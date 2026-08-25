package LibpgQuery::NodeSupport::Enums;

# Collects the enum definitions needed for the enum helper functions and the
# protobuf definition. gen_node_support.pl itself only records enum type names,
# so we parse the member lists ourselves.

use strict;
use warnings FATAL => 'all';

use LibpgQuery::NodeSupport::Common qw(elem);

# Headers whose enums get helper functions and protobuf definitions, in
# output order
my @ENUM_HEADERS = (
	'nodes/parsenodes.h', 'nodes/primnodes.h', 'nodes/nodes.h',
	'nodes/lockoptions.h', 'access/cmptype.h',
);

# Enums that are handled differently and thus excluded here
my @SKIP_ENUMS = ('NodeTag');

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

# Returns { enums => [ { name => ..., members => [ ... ] }, ... ] (in
# declaration order), scan_tokens => [ [ name, value ], ... ] }
sub parse
{
	my ($ctx) = @_;
	my @enums;

	foreach my $header (@ENUM_HEADERS)
	{
		my $content = read_without_comments("$ctx->{srcdir}/src/include/$header");

		while ($content =~ /typedef\s+enum\s+(\w+)\s*\{(.*?)\}\s*\1\s*;/sg)
		{
			my ($name, $body) = ($1, $2);
			next if elem $name, @SKIP_ENUMS;

			die "enum $name from $header is unknown to gen_node_support.pl\n"
			  unless elem $name, @{ $ctx->{enum_types} };

			my @members;
			foreach my $piece (split /,/, $body)
			{
				push @members, $1 if $piece =~ /^\s*(\w+)/;
			}
			die "enum $name from $header has no members\n" unless @members;

			push @enums, { name => $name, members => \@members };
		}
	}

	# Scanner tokens, from the bison-generated parser header
	my $gram = read_without_comments("$ctx->{srcdir}/src/backend/parser/gram.h");
	$gram =~ /enum\s+yytokentype\s*\{(.*?)\}/s
	  or die "could not find yytokentype in gram.h\n";
	my $body = $1;
	my @scan_tokens;
	while ($body =~ /(\w+)\s*=\s*(-?\d+)/g)
	{
		push @scan_tokens, [ $1, $2 ];
	}
	die "no scanner tokens found in gram.h\n" unless @scan_tokens;

	return { enums => \@enums, scan_tokens => \@scan_tokens };
}

1;
