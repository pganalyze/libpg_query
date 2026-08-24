package LibpgQuery::NodeSupport::Hook;

# Entry point for the --hook option of the patched gen_node_support.pl (see
# patches/13_gen_node_support_hook.patch). The generator loads this file after
# it has parsed all node headers, and calls the code reference it returns with
# the collected node type information, which we use to generate libpg_query's
# node support files (see scripts/generate_node_support.sh).
#
# All libpg_query-specific policy lives in overrides.pl, the generation logic
# in the modules under lib/.

use strict;
use warnings FATAL => 'all';
use File::Basename qw(dirname);
use lib dirname(__FILE__) . '/lib';

use LibpgQuery::NodeSupport::Fingerprint;

my $overrides_file = dirname(__FILE__) . '/overrides.pl';
my $overrides = do $overrides_file;
die "could not load $overrides_file: " . ($@ || $!) . "\n"
  unless ref($overrides) eq 'HASH';

return sub {
	my ($ctx) = @_;

	LibpgQuery::NodeSupport::Fingerprint::generate($ctx, $overrides);
};
