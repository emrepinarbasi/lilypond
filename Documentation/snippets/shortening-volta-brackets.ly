%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.13.39"

\header {
  lsrtags = "repeats"

%% Translation of GIT committish: 5160eccb26cee0bfd802d844233e4a8d795a1e94
  texidoces = "
De forma predeterminada, los corchetes de primera y segunda vez se
trazan encima de los finales alternativos completos, pero es posible
acortartlos estableciendo un valor cierto para
@code{voltaSpannerDuration}.  En el ejemplo siguiente, el corchete
sólo dura un compás, que corresponde a una duración de 3/4.

"
  doctitlees = "Acortar los corchetes de primera y segunda vez"


%% Translation of GIT committish: 0a868be38a775ecb1ef935b079000cebbc64de40
  texidocde = "
Volta-Klammern werden normalerweise über alle Noten der Klammer gezogen, aber
es ist möglich sie zu verkürzen.  Hierzu muss
@code{voltaSpannerDuration} definiert werden, in dem Beispiel etwa als
3/4, sodass die Klammer nur einen Takt dauert.

"
  doctitlede = "Volta-Klammern verkürzen"

%% Translation of GIT committish: a5bde6d51a5c88e952d95ae36c61a5efc22ba441
  texidocfr = "
Les crochets indiquant les fins alternatives s'étalent tout au long ce
celle-ci.  On peut les raccourcir en définissant la propriété
@code{voltaSpannerDuration}.  Dans l'exemple suivant, le crochet ne se
prolonge que sur une mesure à 3/4.

"
  doctitlefr = "Diminution de la taille du crochet d'alternative"


  texidoc = "
By default, the volta brackets will be drawn over all of the
alternative music, but it is possible to shorten them by setting
@code{voltaSpannerDuration}.  In the next example, the bracket only
lasts one measure, which is a duration of 3/4.

"
  doctitle = "Shortening volta brackets"
} % begin verbatim

\relative c'' {
  \time 3/4
  c4 c c
  \set Score.voltaSpannerDuration = #(ly:make-moment 3 4)
  \repeat volta 5 { d4 d d }
  \alternative {
    {
      e4 e e
      f4 f f
    }
    { g4 g g }
  }
}

