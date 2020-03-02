\version "2.19.21"

\header {
  lsrtags = "fretted-strings"

  texidoc = "
When automatic fretboards are used, barre indicators will be drawn whenever
one finger is responsible for multiple strings.

If no finger indications are given in the chord from which the automatic
fretboard is created, no barre indicators will be included, because
there is no way to identify where barres should be placed.

"
  doctitle = "Barres in automatic fretboards"
}

\new FretBoards {
  <f,-1 c-3 f-4 a-2 c'-1 f'-1>1
  <f, c f a c' f'>1
}

