\version "1.7.18"
% TODO: check if this is the best filename.  Look for other
% followvoice examples in input/test
\header{
	texidoc = "@cindex Piano followVoice
followVoice: connect note heads with line when thread switches staff."
}
\score{
    \context PianoStaff <
        \context Staff=one \notes\relative c''{
	    \context Thread
            a1 \break
	    \translator Staff=two
	    a,

	}
	\context Staff=two { \clef bass \skip 1*2 }
    >
    \paper{
        linewidth = 70.\mm
	\translator {
	    \ScoreContext
	    followVoice = ##t
	}
    }
}
%% new-chords-done %%
