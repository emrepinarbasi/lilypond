
$(O_FILES): $(outdir)/config.hh

$(LIBRARY): $(O_FILES)
	$(call ly_progress,Making,$@,)
	$(AR) $(ARFLAGS) $@ $(O_FILES)
# thanks to Nelson Beebe for this trick.
	$(RANLIB) $@ || $(AR) ts $@ || true



