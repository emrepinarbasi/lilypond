
\version "1.3.141";

instrument = "Flute"

\include "header.ly"
\include "global.ly"
\include "flauti.ly"

\score{
	\flautiStaff
	\include "coriolan-part-paper.ly"
	\include "coriolan-midi.ly"
}

