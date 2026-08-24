package LibpgQuery::NodeSupport::Fingerprint;

# Generates pg_query_fingerprint_defs.c / pg_query_fingerprint_conds.c: the
# fingerprint functions for the raw parse tree nodes, included by
# pg_query_fingerprint.c, which also provides the runtime helpers the
# generated code relies on (_fingerprintChild*, _fingerprint*Field and the
# custom handlers). Per-node/per-field policy comes from overrides.pl.

use strict;
use warnings FATAL => 'all';

use LibpgQuery::NodeSupport::Common qw(elem write_file node_fields parse_tree_nodes);

my @INT_TYPES = qw(bits32 uint32 int int32 uint16 int16 Oid Index
  AttrNumber SubTransactionId RelFileNumber ParseLoc);
my @UINT64_TYPES = qw(uint64 AclMode);
my @BITMAPSET_TYPES = ('Bitmapset*', 'Bitmapset', 'Relids');
my @FLOAT_TYPES = qw(Cost double Cardinality);

# Scalar field handled by one of the _fingerprint*Field helpers
sub scalar_field
{
	my ($helper, $f) = @_;
	return "  ${helper}(ctx, \"$f\", node->$f);\n\n";
}

sub generate
{
	my ($ctx, $ov) = @_;
	my $info = $ctx->{node_type_info};
	my @node_types = @{ $ctx->{node_types} };
	my @abstract_types = @{ $ctx->{abstract_types} };
	my @enum_types = @{ $ctx->{enum_types} };

	my %exclude = map { $_ => 1 } @{ $ov->{fingerprint_exclude_nodes} || [] };
	my %skip_all = map { $_ => 1 } @{ $ov->{fingerprint_skip_all_nodes} || [] };
	my %custom_body =
	  map { $_ => 1 } @{ $ov->{fingerprint_custom_body_nodes} || [] };
	my %omit_fields = %{ $ov->{fingerprint_omit_fields} || {} };
	my %skip_fields = %{ $ov->{fingerprint_skip_fields} || {} };
	my %custom_fields = %{ $ov->{fingerprint_custom_fields} || {} };
	my %conds_wrap = %{ $ov->{fingerprint_conds_wrap} || {} };

	my @nodes = parse_tree_nodes($ctx);

	# generate fingerprint function bodies
	my %defs;
	foreach my $n (@nodes)
	{
		next if elem $n, @abstract_types;
		next if defined $info->{$n}->{alias_of};
		next if $exclude{$n};

		if ($custom_body{$n})
		{
			# hand-written body lives in pg_query_fingerprint.c
			$defs{$n} = undef;
			next;
		}

		if ($skip_all{$n})
		{
			$defs{$n} =
			  "  // Intentionally ignoring all fields for fingerprinting\n";
			next;
		}

		my $def = '';
		foreach my $fe (sort { $a->[0] cmp $b->[0] } node_fields($ctx, $n))
		{
			my ($f, $t) = @$fe;

			next if $omit_fields{"$n.$f"};

			if ($custom_fields{"$n.$f"})
			{
				# hand-written field handler in pg_query_fingerprint.c
				$def .=
				  "  _fingerprint${n}_${f}(ctx, node, parent, field_name, depth);\n\n";
				next;
			}

			if ($skip_fields{"$n.$f"} || $skip_fields{$f})
			{
				$def .=
				  "  // Intentionally ignoring node->$f for fingerprinting\n\n";
				next;
			}

			if ($t eq 'Node')
			{
				$def .=
				  "  _fingerprintChildNode(ctx, &node->$f, node, \"$f\", depth);\n\n";
			}
			elsif ($t eq 'Datum'
				or $t eq 'void*'
				or $t eq 'Expr'
				or $t eq 'NodeTag')
			{
				# ignore
			}
			elsif ($t !~ /\*/ and elem $t, @abstract_types)
			{
				# embedded abstract node
				$def .=
				  "  _fingerprintChildNode(ctx, &node->$f, node, \"$f\", depth);\n\n";
			}
			elsif ($t eq 'Node*'
				or ($t =~ /^(\w+)\*$/ and elem $1, @abstract_types))
			{
				# pointer to a node of a type only known at runtime
				# (includes Expr* and other abstract node types)
				$def .= <<"EOT";
  if (node->$f != NULL)
    _fingerprintChildNode(ctx, node->$f, node, "$f", depth);

EOT
			}
			elsif ($t eq 'List*')
			{
				$def .= <<"EOT";
  if (node->$f != NULL && node->$f->length > 0)
    _fingerprintChildList(ctx, node->$f, node, "$f", depth);

EOT
			}
			elsif ($t eq 'char')
			{
				$def .= scalar_field('_fingerprintCharField', $f);
			}
			elsif ($t eq 'char*')
			{
				$def .= scalar_field('_fingerprintStringField', $f);
			}
			elsif ($t eq 'String*')
			{
				$def .= scalar_field('_fingerprintStringNodeField', $f);
			}
			elsif ($t eq 'bool')
			{
				$def .= scalar_field('_fingerprintBoolField', $f);
			}
			elsif (elem $t, @INT_TYPES)
			{
				$def .= scalar_field('_fingerprintIntField', $f);
			}
			elsif ($t eq 'long')
			{
				$def .= scalar_field('_fingerprintLongField', $f);
			}
			elsif (elem $t, @UINT64_TYPES)
			{
				$def .= scalar_field('_fingerprintUInt64Field', $f);
			}
			elsif (elem $t, @BITMAPSET_TYPES)
			{
				$def .= scalar_field('_fingerprintBitmapsetField', $f);
			}
			elsif (elem $t, @FLOAT_TYPES)
			{
				$def .= scalar_field('_fingerprintFloatField', $f);
			}
			elsif ($t !~ /\*/ and elem $t, @nodes)
			{
				# embedded node struct (e.g. CreateForeignTableStmt.base);
				# note this passes depth as-is, not depth + 1
				$def .= "  _fingerprintString(ctx, \"$f\");\n";
				$def .=
				  "  _fingerprint${t}(ctx, (const ${t}*) &node->$f, node, \"$f\", depth);\n";
			}
			elsif ($t =~ /^(\w+)\*$/ and elem $1, @node_types)
			{
				# pointer to a node of a statically known type; unlike the
				# generic node pointer case above this does not add the
				# type name to the fingerprint (historic behavior)
				$def .= <<"EOT";
  if (node->$f != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "$f");
    _fingerprint$1(ctx, node->$f, node, "$f", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

EOT
			}
			elsif (elem $t, @enum_types)
			{
				$def .=
				  "  _fingerprintEnumField(ctx, \"$f\", _enumToString${t}(node->$f));\n\n";
			}
			else
			{
				die
				  "could not handle type \"$t\" in struct \"$n\" field \"$f\" for fingerprinting\n";
			}
		}
		$defs{$n} = $def;
	}

	# assemble output files
	my $defs_out = '';
	my $conds_out = '';

	foreach my $n (@nodes)
	{
		next unless exists $defs{$n};
		$defs_out .=
		  "static void _fingerprint${n}(FingerprintContext *ctx, const ${n} *node, const void *parent, const char *field_name, unsigned int depth);\n";
	}
	$defs_out .= "\n\n";

	foreach my $n (@nodes)
	{
		next unless exists $defs{$n};

		if (defined $defs{$n})
		{
			$defs_out .= "static void\n";
			$defs_out .=
			  "_fingerprint${n}(FingerprintContext *ctx, const ${n} *node, const void *parent, const char *field_name, unsigned int depth)\n";
			$defs_out .= "{\n";
			$defs_out .= $defs{$n};
			$defs_out .= "}\n";
			$defs_out .= "\n";
		}
		else
		{
			$defs_out .=
			  "// _fingerprint${n} has a custom implementation, see pg_query_fingerprint.c\n\n";
		}

		$conds_out .= "case T_${n}:\n";
		if ($skip_all{$n})
		{
			$conds_out .= "  // Intentionally ignoring for fingerprinting\n";
		}
		else
		{
			$conds_out .= $conds_wrap{$n} if exists $conds_wrap{$n};
			$conds_out .= "  _fingerprintString(ctx, \"${n}\");\n";
			$conds_out .=
			  "  _fingerprint${n}(ctx, obj, parent, field_name, depth);\n";
			$conds_out .= "  }\n" if exists $conds_wrap{$n};
		}
		$conds_out .= "  break;\n";
	}

	write_file("$ctx->{outdir}/pg_query_fingerprint_defs.c", $defs_out);
	write_file("$ctx->{outdir}/pg_query_fingerprint_conds.c", $conds_out);
	return;
}

1;
