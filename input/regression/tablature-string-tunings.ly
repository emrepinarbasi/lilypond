\header {

    texidoc = "For other tunings, it is sufficient to set
    @code{stringTunings}. The number of staff lines is adjusted
    accordingly."

}

\version "2.3.17"

\score  {
     \new TabStaff {
	\set TabStaff.stringTunings = #'(5  10 15 20)
	\relative c''  { c4 d e f }
       }
}
 
