%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.di.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.20.0"

\header {
  lsrtags = "scheme-language"

  texidoc = "
You can add additional elements to notes using @code{map-some-music}.
In this example, an extra script is attached to a note.

In general, first do a @code{\\displayMusic} of the music you want to
create, then write a function that will work on the appropriate parts
of the music for you.

"
  doctitle = "Adding extra fingering with scheme"
} % begin verbatim

addScript =
#(define-music-function (script music)
   (ly:event? ly:music?)
   (map-some-music
    (lambda (mus)
      (define (append-script-at! prop)
        (set! (ly:music-property mus prop)
              (append (ly:music-property mus prop)
                      (list (ly:music-deep-copy script))))
        mus)
      (case (ly:music-property mus 'name)
        ((EventChord)
         (append-script-at! 'elements))
        ((NoteEvent)
         (append-script-at! 'articulations))
        (else #f)))
    music))

\score {
  {
    \addScript _6 { c'4-3 <c' e' g'> }
  }
}
