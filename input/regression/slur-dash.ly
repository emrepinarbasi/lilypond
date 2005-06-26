\version "2.6.0"
\header {texidoc = "@cindex Slur, dotted, dashed
The appearance of slurs may be changed from solid to dotted or dashed.
"
} 
\score{
	\relative c'{
		c( d e  c) |
		\slurDotted
		c( d e  c) |
		\slurDashed
		c( d e  c) |
		\override Slur #'dash-period = #2.0
		\override Slur #'dash-fraction = #0.4
		c( d e  c) |
		\slurSolid
		c( d e  c) |
	}
	\layout{ raggedright=##t }
}



