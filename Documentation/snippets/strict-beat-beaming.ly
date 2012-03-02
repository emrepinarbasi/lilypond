% DO NOT EDIT this file manually; it is automatically
% generated from Documentation/snippets/new
% Make any changes in Documentation/snippets/new/
% and then run scripts/auxiliar/makelsr.py
%
% This file is in the public domain.
%% Note: this file works from version 2.15.28
\version "2.15.28"

\header {
%% Translation of GIT committish: 5a7301fc350ffc3ab5bd3a2084c91666c9e9a549
  texidoces = "
Se puede hacer que las barras secundarias apunten en la dirección del
pulso o fracción a que pertenecen.  La primera barra evita los
corchetes sueltos (que es el comportamiento predeterminado); la
segunda barra sigue el pulso o fracción estrictamente.

"
  doctitlees = "Barras que se atienen al pulso estrictamente"

%% Translation of GIT committish: fc1ca638e0b5f66858b9b7a073ceefc1eccb3ed2

  texidocde = "
Sekundäre Balken können in die Richtung gesetzt werden, die ihrer rhythmischen
Zugehörigkeit entspricht.  Der erste Balken ist zusammengefasst (Standard),
der zweite Sechszehntelbalken zeigt den Taktschlag an.
"

  doctitlede = "Bebalkung nach Taktschlag"



%% Translation of GIT committish: af3df3b7c6e062635bdccb739be41962969806a0
  texidocfr = "
Une sous-ligature tronquée peut pointer en direction de la pulsation à
laquelle elle se rattache.  Dans l'exemple suivant, la première ligature
évite toute troncature (comportement par défaut), alors que la deuxième
respecte rigoureusement la pulsation.

"

  doctitlefr = "Ligature à la pulsation"

  texidoc = "
Beamlets can be set to point in the direction of the beat to which they
belong.  The first beam avoids sticking out flags (the default);
the second beam strictly follows the beat.
"

  doctitle = "Strict beat beaming"

  lsrtags = "rhythms"
} % begin verbatim



\relative c'' {
  \time 6/8
  a8. a16 a a
  \set strictBeatBeaming = ##t
  a8. a16 a a
}
