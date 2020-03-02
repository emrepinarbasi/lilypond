.SUFFIXES: .html .xml .lytex .tex .latex .lyxml .tely .texi .texinfo

############## HTML #########################

$(outdir)/%.html:  %.html
	$(call ly_progress,Making,$@,< html)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<

$(outdir)/%.html:  %.htmly
	$(call ly_progress,Making,$@,< htmly)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<

$(outdir)/%.html:  %.xml
	$(call ly_progress,Making,$@,< xml)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<


############## LaTeX ########################

$(outdir)/%.tex:  %.lytex
	$(call ly_progress,Making,$@,< lytex)
	$(buildscript-dir)/run-and-check "$(LILYPOND_BOOK_COMMAND) --pdf -o $(outdir) $<"  $(outdir)/"$*.lytex.log"

$(outdir)/%.tex:  %.tex
	$(call ly_progress,Making,$@,< tex)
	$(LILYPOND_BOOK_COMMAND) --pdf -o $(outdir) $<

$(outdir)/%.tex:  %.latex
	$(call ly_progress,Making,$@,< latex)
	$(LILYPOND_BOOK_COMMAND) --pdf -o $(outdir) $<

# Add the tex => pdf rule only if we have pdflatex
ifeq (,$(findstring pdflatex,$(MISSING_OPTIONAL)))
$(outdir)/%.pdf:  $(outdir)/%.tex
	$(call ly_progress,Making,$@,< tex)
	rm -fr $(outdir)/$*.build/
	mkdir $(outdir)/$*.build
	cd $(outdir) && $(buildscript-dir)/run-and-check \
		"$(PDFLATEX) -interaction=nonstopmode -halt-on-error \
			-output-directory=$*.build \
			$(notdir $<)" \
		"$*.pdflatex.log"
ifeq ($(USE_EXTRACTPDFMARK),yes)
	$(EXTRACTPDFMARK) -o $(outdir)/$*.pdfmark $(outdir)/$*.build/$*.pdf
	$(GS920) -dBATCH \
                 -dNOSAFER \
                 -dNOPAUSE \
                 $(LILYPOND_BOOK_GS_QUIET) \
                 -sDEVICE=pdfwrite \
                 -dAutoRotatePages=/None \
                 -dPrinted=false \
                 -sOutputFile=$@ \
                 -c "30000000 setvmthreshold" \
                 -f $(top-build-dir)/out-fonts/*.font.ps \
                 $(outdir)/$*.pdfmark \
                 $(outdir)/$*.build/$*.pdf
else
	mv $(outdir)/$*.build/$*.pdf $@
endif
	rm -fr $(outdir)/$*.build/
endif

############## Texinfo ######################

$(outdir)/%.texi:  %.texi
	$(call ly_progress,Making,$@,< texi)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<

$(outdir)/%.texi:  %.itexi
	$(call ly_progress,Making,$@,< itexi)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<

$(outdir)/%.texi:  %.texinfo
	$(call ly_progress,Making,$@,< texinfo)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<

$(outdir)/%.texi:  %.tely
	$(call ly_progress,Making,$@,< tely)
	$(LILYPOND_BOOK_COMMAND) -o $(outdir) $<


############## DocBook ######################

$(outdir)/%.xml:  %.lyxml
	$(call ly_progress,Making,$@,< lyxml)
	$(LILYPOND_BOOK_COMMAND) --pdf -o $(outdir) $<

# Add the xml => pdf rule only if we have dblatex
ifeq (,$(findstring dblatex,$(MISSING_OPTIONAL)))
$(outdir)/%.pdf:  $(outdir)/%.xml
	$(call ly_progress,Making,$@,< xml)
	cd $(outdir) && $(buildscript-dir)/run-and-check \
		"$(DBLATEX) $(DBLATEX_BACKEND) -o $*.tmp.pdf $(notdir $<)" \
		"$*.dblatex.log"
ifeq ($(USE_EXTRACTPDFMARK),yes)
	$(EXTRACTPDFMARK) -o $(outdir)/$*.pdfmark $(outdir)/$*.tmp.pdf
	$(GS920) -dBATCH \
                 -dNOSAFER \
                 -dNOPAUSE \
                 $(LILYPOND_BOOK_GS_QUIET) \
                 -sDEVICE=pdfwrite \
                 -dAutoRotatePages=/None \
                 -dPrinted=false \
                 -sOutputFile=$@ \
                 -c "30000000 setvmthreshold" \
                 -f $(top-build-dir)/out-fonts/*.font.ps \
                 $(outdir)/$*.pdfmark \
                 $(outdir)/$*.tmp.pdf
	rm $(outdir)/$*.tmp.pdf
else
	mv $(outdir)/$*.tmp.pdf $@
endif
endif
