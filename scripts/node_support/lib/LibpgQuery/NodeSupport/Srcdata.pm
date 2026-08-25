package LibpgQuery::NodeSupport::Srcdata;

# Generates the srcdata/*.json files: machine-readable node struct, enum and
# typedef definitions, published for downstream projects (e.g. language
# bindings) to build on.
#
# Node structs come straight from the gen_node_support.pl parse; enums and
# typedefs are parsed from the headers (gen_node_support.pl doesn't record
# those in detail).

use strict;
use warnings FATAL => 'all';

use JSON::PP;

use LibpgQuery::NodeSupport::Common qw(elem write_file node_fields parse_tree_nodes);
use LibpgQuery::NodeSupport::Enums;

# Headers to extract enums and typedefs from (relative to src/include), also
# the group names in the output
my @GROUPS = (
	'nodes/parsenodes', 'nodes/primnodes', 'nodes/lockoptions',
	'nodes/nodes', 'nodes/params', 'access/attnum', 'access/cmptype', 'c',
	'postgres', 'postgres_ext', 'commands/vacuum', 'storage/block',
	'access/sdir', 'mb/pg_wchar', '../backend/parser/gram',
	'../backend/parser/gramparse',
);

# Typedefs of basic types that are of no interest
my @IGNORE_TYPEDEFS = qw(varlena IntArray nameData bool sig_atomic_t size_t varatt_indirect);

# Node structs with hand-written support in libpg_query, described by hand
# below instead (they contain unions)
my @HAND_WRITTEN_NODES = ('A_Const');

sub struct_defs
{
	my ($ctx) = @_;
	my %defs;

	foreach my $n (parse_tree_nodes($ctx))
	{
		next if defined $ctx->{node_type_info}->{$n}->{alias_of};
		next if elem $n, @HAND_WRITTEN_NODES;

		(my $group = $ctx->{node_type_info}->{$n}->{source_header}) =~ s/\.h$//;
		$defs{$group}->{$n} = {
			fields => [
				map { { name => $_->[0], c_type => $_->[1] } } node_fields($ctx, $n)
			]
		};
	}

	# Value nodes and lists are special-cased in the generated code, describe
	# them by hand
	$defs{'nodes/value'} = {
		Integer => { fields => [ { name => 'ival', c_type => 'long' } ] },
		Float => { fields => [ { name => 'fval', c_type => 'char*' } ] },
		Boolean => { fields => [ { name => 'boolval', c_type => 'bool' } ] },
		String => { fields => [ { name => 'sval', c_type => 'char*' } ] },
		BitString => { fields => [ { name => 'bsval', c_type => 'char*' } ] },
		A_Const => {
			fields => [
				{ name => 'isnull', c_type => 'bool' },
				{ name => 'val', c_type => 'Node' },
			]
		},
	};
	$defs{'nodes/pg_list'} =
	  { List => { fields => [ { name => 'items', c_type => '[]Node' } ] } };

	return \%defs;
}

# Node tags in nodetag order, with the numbers gen_node_support.pl assigns
sub nodetags
{
	my ($ctx) = @_;
	my @tags;
	my $tagno = 0;

	foreach my $n (@{ $ctx->{node_types} }, @{ $ctx->{extra_tags} })
	{
		next if elem $n, @{ $ctx->{abstract_types} };
		my $manual = $ctx->{manual_nodetag_number}->{$n};
		push @tags, { name => $n, value => defined $manual ? $manual : ++$tagno };
	}

	return @tags;
}

# Returns the enum definitions by group, and all enum names in declaration order
sub enum_defs
{
	my ($ctx, $nodetags) = @_;
	my %defs;
	my @names;

	foreach my $group (@GROUPS)
	{
		foreach my $e (LibpgQuery::NodeSupport::Enums::parse_header("$ctx->{srcdir}/src/include/$group.h"))
		{
			my @members = @{ $e->{members} };

			# The node tags are included from the generated nodes/nodetags.h
			if ($e->{name} eq 'NodeTag')
			{
				push @members,
				  map { { name => "T_$_->{name}", value => $_->{value} } } @$nodetags;
			}

			$defs{$group}->{ $e->{name} } = { values => \@members };
			push @names, $e->{name};
		}
	}

	return (\%defs, \@names);
}

sub typedefs
{
	my ($ctx) = @_;
	my @typedefs;

	foreach my $group (@GROUPS)
	{
		my $content = LibpgQuery::NodeSupport::Enums::read_without_comments(
			"$ctx->{srcdir}/src/include/$group.h");

		while ($content =~ /^typedef(?: struct)? ([A-Za-z0-9_ ]+?) \*?([A-Za-z_]\w*);/mg)
		{
			my ($source, $new) = ($1, $2);
			next if elem($source, @IGNORE_TYPEDEFS) or elem($new, @IGNORE_TYPEDEFS);
			push @typedefs, { new_type_name => $new, source_type => $source };
		}
	}

	return \@typedefs;
}

sub generate
{
	my ($ctx) = @_;
	my $outdir = $ctx->{outdir};

	my @nodetags = nodetags($ctx);
	my $struct_defs = struct_defs($ctx);
	my ($enum_defs, $all_known_enums) = enum_defs($ctx, \@nodetags);
	my $typedefs = typedefs($ctx);

	my $json = JSON::PP->new->pretty->canonical;
	write_file("$outdir/nodetypes.json", $json->encode([ map { $_->{name} } @nodetags ]));
	write_file("$outdir/all_known_enums.json", $json->encode($all_known_enums));
	write_file("$outdir/struct_defs.json", $json->encode($struct_defs));
	write_file("$outdir/enum_defs.json", $json->encode($enum_defs));
	write_file("$outdir/typedefs.json", $json->encode($typedefs));
	return;
}

1;
