%
% spacing info for LilyPond. Do not edit this.
% It has a lot of hard-wired stringconstants
%

table_twenty = \symboltables {

    texid 	"\musixtwentydefs"

     "style" = \table {
		"roman"	"\settext{%}" 0pt 0pt 0pt 0pt
		"italic"	"\setitalic{%}" 0pt 0pt 0pt 0pt
     }
     "align" = \table {
		"-1"	"\leftalign{%}" 0pt 0pt 0pt 0pt
		"0"	"\centeralign{%}" 0pt 0pt 0pt 0pt
		"1"	"\rightalign{%}" 0pt 0pt 0pt 0pt
 	}


    % index TeXstring, 	xmin xmax ymin ymax
    % be careful with editing this:
    % the "index" entry is hardwired into lilypond.

    "clefs" = \table {
	    "violin"	"\violinclef" 	0pt	16pt	-12.5pt	22.5pt
	    "bass"	"\bassclef" 		0pt	16pt	0pt	20pt
	    "alto"	"\altoclef"	 	0pt	16pt	0pt	20pt
	    "tenor"	"\altoclef"	 	0pt	16pt	0pt	20pt
	    "violin_change"	"\cviolinclef" 	0pt	16pt	-12.5pt	22.5pt
	    "bass_change"	"\cbassclef"	0pt	16pt	0pt	20pt
	    "alto_change"	"\caltoclef" 	0pt	16pt	0pt	20pt
	    "tenor_change"	"\caltoclef" 	0pt	16pt	0pt	20pt
    }

    "balls" = \table {
	    "1"	"\wholeball"	0pt	7.5pt	-2.5pt	2.5pt
	    "2"	"\halfball"	0pt	6pt	-2.5pt	2.5pt
	    "4"	"\quartball"	0pt	6pt	-2.5pt	2.5pt
    }

    "slur" = \table {
	    "whole"	"\slurchar%{%}"	0pt	0pt	0pt	0pt
	    "half"	"\hslurchar%{%}"	0pt	0pt	0pt	0pt
    }
    "accidentals" = \table {
	    "-2"	"\flatflat"	0pt 	10.2pt	-2.5pt 7.5pt
	    "-1"	"\flat"		0pt	6pt	-2.5pt 7.5pt
	    "0"	"\natural"	0pt	6pt	-7.5pt 7.5pt
	    "1"	"\sharp"		0pt	6pt	-7.5pt 7.5pt
	    "2"	"\sharpsharp"	0pt	6pt	-2.5pt 7.5pt
    }

    "streepjes" = \table {
	    "toplines"	"\toplines{%}"	-3pt	9pt 0pt	0pt
	    "botlines"	"\botlines{%}"	-3pt	9pt 0pt	0pt
    }

    "bars" = \table {
	    "empty"	"\emptybar"	0pt	0pt	0pt	0pt
	    "|"	"\maatstreep"	0pt	5pt 	-12pt	12pt
	    "||"	"\finishbar"	0pt	2pt	-12pt	12pt
    }

    "rests" = \table {
	    "1"	"\wholerest"		-5pt	1pt	-1pt	1pt
	    "2"	"\halfrest"		-5pt	1pt	-1pt	1pt
	    "4"	"\quartrest"		-5pt	2pt	-5pt	5pt
	    "8"	"\eighthrest"		0pt	5pt	0pt	8pt
	    "16"	"\sixteenthrest"		0pt	6pt	0pt	12pt
	    "32"	"\thirtysecondrest"	0pt	6pt	0pt	16pt
    }

    "meters" = \table {
	    "C"	"\fourfourmeter"		0pt	10pt	-5pt	5pt
	    "C2"	"\allabreve"		0pt	10pt	-5pt	5pt
    }

    % dims ignored for this table
    "param" = \table {
	    "meter"	"\generalmeter{%}{%}"	-3pt	10pt	-5pt	5pt
	    "linestaf"	"\linestafsym{%}{%}"	
	    "stem"	"\stem{%}{%}"		
	     "fill"	"\hbox{}"
    }

    "dots" = \table {
	    "1"	"\lsingledot"		0pt	8pt	-1pt	1pt
	    "2"	"\ldoubledot"		0pt	12pt	-1pt	1pt
	    "3"	"\ltripledot"		0pt	16pt	-1pt	1pt
    }

    "flags" = \table {
	    "8"	"\eigthflag"		0pt	5pt	0pt	0pt	
	    "16"	"\sixteenthflag"		0pt	5pt	0pt	0pt
	    "32"	"\thirtysecondflag"	0pt	5pt	0pt	0pt
	    "-8"	"\deigthflag"		0pt	5pt	0pt	0pt
	    "-16"	"\dsixteenthflag"		0pt	5pt	0pt	0pt
	    "-32"	"\dthirtysecondflag"	0pt	5pt	0pt	0pt
    }

    "beamslopes" = \table {
	    "slope"	"\beamslope{%}{%}"
	    "horizontal"	"\rulesym{%}{%}"	
    }

}
default_table = \symboltables { table_twenty }
