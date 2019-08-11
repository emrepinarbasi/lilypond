ALL_LDFLAGS = $(LDFLAGS)
PY_MODULES_IN = $(call src-wildcard,*.py)
OUT_PY_MODULES = $(PY_MODULES_IN:%=$(outdir)/%)
PY_MODULES_NOPY = $(PY_MODULES_IN:.py=)
OUT_PYC_MODULES = $(PY_MODULES_NOPY:%=$(outdir)/__pycache__/%.cpython-37.pyc)
OUT_PYO_MODULES = $(OUT_PY_MODULES:%.py=%.pyo)
ifeq ($(MINGW_BUILD)$(CYGWIN_BUILD),)
SHARED_MODULE_SUFFIX = .so
else
ifneq ($(CYGWIN_BUILD),)
SHARED_MODULE_SUFFIX = .dll
endif
ifneq ($(MINGW_BUILD),)
SHARED_MODULE_SUFFIX = .dll
endif
endif
ifneq ($(DARWIN_BUILD),)
SHARED_FLAGS = -bundle -flat_namespace -undefined suppress
endif
OUT_SO_MODULES = $(addprefix $(outdir)/, $(C_FILES:.c=$(SHARED_MODULE_SUFFIX)))
