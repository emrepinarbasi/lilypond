%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.13.10"

\header {
%% Translation of GIT committish: b7ec64504da87595509ae6e88ae546d6a0ce633d
  texidocfr = "
Pour obtenir la partition d'un chanson, il suffit d'assembler
des noms d'accords, une mélodie et des paroles :

"
  doctitlefr = "Chanson simple"

  lsrtags = "chords"

%% Translation of GIT committish: b2d4318d6c53df8469dfa4da09b27c15a374d0ca
  texidoces = "
Al juntar nombres de acorde en cifrado americano, melodía y letra,
obtenemos una hoja guía de acordes o «lead sheet»:

"
  doctitlees = "Hoja guía de acordes o «lead sheet» sencilla"

%% Translation of GIT committish: d96023d8792c8af202c7cb8508010c0d3648899d
 texidocde = "
Ein Liedblatt besteht aus Akkordbezeichnungen, einer Melodie und dem Liedtext:

"
  doctitlede = "Ein einfaches Liedblatt"

  texidoc = "
When put together, chord names, a melody, and lyrics form a lead sheet:

"
  doctitle = "Simple lead sheet"
} % begin verbatim

<<
  \chords { c2 g:sus4 f e }
  \relative c'' {
    a4 e c8 e r4
    b2 c4( d)
  }
  \addlyrics { One day this shall be free __ }
>>

