\version "2.3.17"
\header {

    texidoc = "For knees, the spacing correction is such that the
stems are put at regular distances. This effect takes into account the
width of the note heads and the thickness of the stem.
"
    }
\score { 
{
 g''8[ g g'' g''] 

 % check code independent of default settings.
 \override NoteSpacing  #'knee-spacing-correction = #1.0 
 g''8[ g g'' g''] 
 \override Stem  #'thickness = #10 
 g''8[ g g'' g''] 
    }
\paper { raggedright = ##t}
     }


