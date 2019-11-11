# make/Stepmake.make

# Use alternate configurations alongside eachother:
#
#     ./configure --enable-config=debug
#     make conf=debug
#
# uses config-debug.make and config-debug.h; output goes to out-debug.
#
ifdef conf
  CONFIGSUFFIX=-$(conf)
endif

# Use same configuration, but different output directory:
#
#     make out=www
#
# uses config.make and config.h; output goes to out-www.
#
ifdef out
  outbase=out-$(out)
else
  outbase=out$(CONFIGSUFFIX)
endif

ifdef config
  config_make=$(config)
else
  config_make=$(depth)/config$(CONFIGSUFFIX).make
endif

outroot=.

include $(config_make)

include $(depth)/make/toplevel-version.make

#
# suggested settings
#
# CPU_COUNT=2   ## for SMP/Multicore machine
# 
-include $(depth)/local.make

MICRO_VERSION=$(PATCH_LEVEL)
BUILD_VERSION=1


outdir=$(outroot)/$(outbase)

# why not generic ??
config_h=$(top-build-dir)/config$(CONFIGSUFFIX).hh

# The outdir that was configured for: best guess to find binaries
outconfbase=out$(CONFIGSUFFIX)
outconfdir=$(outroot)/$(outconfbase)

# user package
stepdir = $(stepmake)/stepmake
# for stepmake package
# stepdir = $(depth)/stepmake

STEPMAKE_TEMPLATES := generic $(STEPMAKE_TEMPLATES)
LOCALSTEPMAKE_TEMPLATES:= generic $(LOCALSTEPMAKE_TEMPLATES)

# Don't try to outsmart us, you puny computer!
# Well, UGH.  This only removes builtin rules from
# subsequent $(MAKE)s, *not* from the current run!
ifeq ($(BUILTINS_REMOVED),)
  export BUILTINS_REMOVED = yes
  MAKE:=$(MAKE) --no-builtin-rules
  include $(stepdir)/no-builtin-rules.make
endif
.SUFFIXES:

# Keep this empty to prevent make from removing intermediate files.
.SECONDARY:

all:

-include $(addprefix $(depth)/make/,$(addsuffix -inclusions.make, $(LOCALSTEPMAKE_TEMPLATES)))

-include $(addprefix $(stepdir)/,$(addsuffix -inclusions.make, $(STEPMAKE_TEMPLATES)))


include $(addprefix $(stepdir)/,$(addsuffix -vars.make, $(STEPMAKE_TEMPLATES)))

# ugh. need to do this because of PATH :=$(top-src-dir)/..:$(PATH)
include $(addprefix $(depth)/make/,$(addsuffix -vars.make, $(LOCALSTEPMAKE_TEMPLATES)))


include $(addprefix $(depth)/make/,$(addsuffix -rules.make, $(LOCALSTEPMAKE_TEMPLATES)))
include $(addprefix $(stepdir)/,$(addsuffix -rules.make, $(STEPMAKE_TEMPLATES)))
include $(addprefix $(depth)/make/,$(addsuffix -targets.make, $(LOCALSTEPMAKE_TEMPLATES)))
include $(addprefix $(stepdir)/,$(addsuffix -targets.make, $(STEPMAKE_TEMPLATES)))
