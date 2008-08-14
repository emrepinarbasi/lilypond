%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.55"

\header {
  lsrtags = "staff-notation, editorial-annotations"

  texidoces = "
Se puede engrosar una línea del pentagrama con fines pedagógicos
(p.ej. la tercera línea o la de la clave de Sol).  Esto se puede
conseguir añadiendo más líneas muy cerca de la línea que se quiere
destacar, utilizando la propiedad @code{line-positions} del objeto
@code{StaffSymbol}.

"
  doctitlees = "Hacer unas líneas del pentagrama más gruesas que las otras"

  texidoc = "
For pedagogical purposes, a staff line can be thickened (e.g., the
middle line, or to emphasize the line of the G clef).  This can be
achieved by adding extra lines very close to the line that should be
emphasized, using the @code{line-positions} property of the
@code{StaffSymbol} object. 

"
  doctitle = "Making some staff lines thicker than the others"
} % begin verbatim
{
  \override Staff.StaffSymbol #'line-positions = #'(-4 -2 -0.2 0 0.2 2 4)
  d'4 e' f' g'
}
