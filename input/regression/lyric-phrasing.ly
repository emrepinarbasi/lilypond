\version "2.3.17"
\header {

texidoc = "
  Normally, the lyric is centered on the note head. However, on
  melismata, the text is left aligned on the left-side of the note head.

"
}


\score{
    <<
	 \relative c' \context Voice = "bla" {
	    \autoBeamOff
	    c4( c16 d c b)  c4
	    d16[ e f g]
	    
	}
	\lyricsto "bla" \context Lyrics \lyricmode {
	    alllll __ tijd
	    izzz
	}
    >>
    \paper { raggedright = ##t }
}
