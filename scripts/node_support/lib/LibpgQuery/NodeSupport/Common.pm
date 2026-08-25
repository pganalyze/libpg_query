package LibpgQuery::NodeSupport::Common;

# Helpers shared by the node support generators.

use strict;
use warnings FATAL => 'all';
use Exporter 'import';

our @EXPORT_OK = qw(elem write_file node_fields parse_tree_nodes underscore);

# Header files defining the raw parse tree nodes libpg_query works with
my @PARSE_TREE_HEADERS = ('nodes/parsenodes.h', 'nodes/primnodes.h');

# Test whether first argument is element of the list in the second argument
sub elem
{
	my $x = shift;
	return grep { $_ eq $x } @_;
}

# Converts CamelCase names to snake_case, for protobuf field and message
# names. This intentionally reproduces the behavior of the Ruby method used
# by the previous generator (an ActiveSupport-derived "underscore"), including
# its quirk of producing a double underscore for names like "AExpr"
# ("a__expr"), since the results are part of the Protobuf definition.
sub underscore
{
	my ($word) = @_;

	return $word unless $word =~ /[A-Z-]|::/;
	$word =~ s{::}{/}g;
	$word =~ s/^([A-Z\d])([A-Z][a-z])/$1__$2/;
	$word =~ s/([A-Z\d]+[a-z]+)([A-Z][a-z])/$1_$2/g;
	$word =~ s/([a-z\d])([A-Z])/$1_$2/g;
	$word =~ tr/-/_/;
	return lc $word;
}

sub write_file
{
	my ($path, $content) = @_;

	open my $fh, '>', $path or die "could not write $path: $!";
	print {$fh} $content;
	close $fh or die "could not write $path: $!";
	return;
}

# Node types from the raw parse tree headers, in nodetag order
sub parse_tree_nodes
{
	my ($ctx) = @_;
	my $info = $ctx->{node_type_info};

	return grep {
		defined $info->{$_}->{source_header}
		  and elem $info->{$_}->{source_header}, @PARSE_TREE_HEADERS
	} @{ $ctx->{node_types} };
}

# Reconstructs the field list of a node struct as declared: gen_node_support.pl
# flattens the fields of a supertype into the node's field list (as
# "supertype_field.name"), so we drop those and instead put the NodeTag or
# supertype back as a single leading pseudo-field. Returns a list of
# [name, c_type, attrs] entries, with c_type normalized (no "struct " prefix).
sub node_fields
{
	my ($ctx, $n) = @_;
	my $info = $ctx->{node_type_info}->{$n};
	my @fields;

	if (defined $info->{supertype})
	{
		push @fields, [ $info->{supertype_field}, $info->{supertype}, [] ];
	}
	else
	{
		push @fields, [ 'type', 'NodeTag', [] ];
	}

	foreach my $f (@{ $info->{fields} })
	{
		next if $f =~ /\./;
		my $t = $info->{field_types}{$f};
		$t =~ s/^struct\s+//;
		push @fields, [ $f, $t, $info->{field_attrs}{$f} || [] ];
	}

	return @fields;
}

1;
