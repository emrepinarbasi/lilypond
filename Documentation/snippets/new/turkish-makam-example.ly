\version "2.20.0"

\header {
  lsrtags = "pitches, version-specific, world-music"

  texidoc = "
This template uses the start of a well-known Turkish Saz Semai that is
familiar in the repertoire in order to illustrate some of the elements
of Turkish music notation.
"
  doctitle = "Turkish Makam example"
}

% Initialize makam settings
\include "turkish-makam.ly"

\header {
    title = "Hüseyni Saz Semaisi"
    composer = "Lavtacı Andon"
}

\relative {
  \set Staff.extraNatural = ##f
  \set Staff.autoBeaming = ##f

  \key a \huseyni
  \time 10/8

  a'4 g'16 [fb] e8. [d16] d [c d e] c [d c8] bfc |
  a16 [bfc a8] bfc c16 [d c8] d16 [e d8] e4 fb8 |
  d4 a'8 a16 [g fb e] fb8 [g] a8. [b16] a16 [g] |
  g4 g16 [fb] fb8. [e16] e [g fb e] e4 r8 |
}
