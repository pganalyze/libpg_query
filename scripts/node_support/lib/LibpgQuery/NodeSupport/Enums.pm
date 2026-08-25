package LibpgQuery::NodeSupport::Enums;

# Parses enum definitions from Postgres headers. gen_node_support.pl itself
# only records enum type names, so the member lists (needed for the enum
# helper functions, the protobuf definition and the srcdata JSON) are parsed
# here.

use strict;
use warnings FATAL => 'all';

use LibpgQuery::NodeSupport::Common qw(elem);

# Headers whose enums get helper functions and protobuf definitions, in
# output order
my @OUTFUNCS_ENUM_HEADERS = (
	'nodes/parsenodes.h', 'nodes/primnodes.h', 'nodes/nodes.h',
	'nodes/lockoptions.h', 'access/cmptype.h',
);

sub read_without_comments
{
	my ($path) = @_;

	open my $fh, '<', $path or die "could not open $path: $!";
	my $content = do { local $/; <$fh> };
	close $fh;

	$content =~ s{/\*.*?\*/}{}gs;    # C comments
	$content =~ s/^\s*#.*$//mg;       # preprocessor lines
	return $content;
}

# Numeric constants #defined in a header, which enum values may refer to
sub defined_constants
{
	my ($path) = @_;

	open my $fh, '<', $path or die "could not open $path: $!";
	my $content = do { local $/; <$fh> };
	close $fh;

	$content =~ s{/\*.*?\*/}{}gs;
	my %constants;
	while ($content =~ /^\s*#\s*define\s+(\w+)\s+\(?(0x[0-9a-fA-F]+|\d+)\)?\s*$/mg)
	{
		my ($name, $value) = ($1, $2);
		$constants{$name} = $value =~ /^0x/ ? hex($value) : $value + 0;
	}
	return %constants;
}

# Evaluates the (limited set of) value expressions used in enum definitions
sub member_value
{
	my ($enum, $expr, $known) = @_;

	$expr =~ s/^\s+|\s+$//g;
	$expr = $1 while $expr =~ /^\((.*)\)$/;

	if ($expr =~ /\|/)
	{
		my $value = 0;
		$value |= member_value($enum, $_, $known) for split /\|/, $expr;
		return $value;
	}
	return $expr + 0 if $expr =~ /^-?\d+$/;
	return hex($expr) if $expr =~ /^0x[0-9a-fA-F]+$/;
	return ($1 << $2) if $expr =~ /^(\d+)\s*<<\s*(\d+)$/;
	return 0x7FFFFFFF if $expr eq 'PG_INT32_MAX';
	return ord($1) if $expr =~ /^'(.)'$/;
	return $known->{$expr} if exists $known->{$expr};    # earlier member or #define
	die "unsupported value \"$expr\" in enum $enum\n";
}

# Parses all enum definitions in a header. Returns a list of
# { name => ..., members => [ { name => ..., value => ... }, ... ] } in
# declaration order.
sub parse_header
{
	my ($path) = @_;
	my $content = read_without_comments($path);
	my %constants = defined_constants($path);
	my @enums;

	while ($content =~ /(?:typedef\s+)?enum\s+(\w+)\s*\{(.*?)\}/sg)
	{
		my ($name, $body) = ($1, $2);
		my @members;
		my %known = %constants;
		my $previous = -1;

		foreach my $piece (split /,/, $body)
		{
			next unless $piece =~ /^\s*(\w+)\s*(?:=\s*(.+?))?\s*$/s;
			my ($member, $expr) = ($1, $2);
			my $value =
			  defined $expr ? member_value($name, $expr, \%known) : $previous + 1;
			push @members, { name => $member, value => $value };
			$known{$member} = $value;
			$previous = $value;
		}
		die "enum $name in $path has no members\n" unless @members;

		push @enums, { name => $name, members => \@members };
	}

	return @enums;
}

# Enums for the output functions and protobuf definition: returns
# { enums => [ { name, members => [ names ] }, ... ], scan_tokens => [ [ name,
# value ], ... ] }
sub parse
{
	my ($ctx) = @_;
	my @enums;

	foreach my $header (@OUTFUNCS_ENUM_HEADERS)
	{
		foreach my $e (parse_header("$ctx->{srcdir}/src/include/$header"))
		{
			# NodeTag is handled via the Node oneof instead
			next if $e->{name} eq 'NodeTag';

			die "enum $e->{name} from $header is unknown to gen_node_support.pl\n"
			  unless elem $e->{name}, @{ $ctx->{enum_types} };

			push @enums,
			  {
				name => $e->{name},
				members => [ map { $_->{name} } @{ $e->{members} } ]
			  };
		}
	}

	# Scanner tokens, from the bison-generated parser header
	my ($tokens) = grep { $_->{name} eq 'yytokentype' }
	  parse_header("$ctx->{srcdir}/src/backend/parser/gram.h");
	die "could not find yytokentype in gram.h\n" unless $tokens;

	return {
		enums => \@enums,
		scan_tokens => [ map { [ $_->{name}, $_->{value} ] } @{ $tokens->{members} } ],
	};
}

1;
