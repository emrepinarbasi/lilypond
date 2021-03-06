\version "2.19.12"

\header {
  lsrtags = "text"

  texidoc = "
Various scripts may be used for texts (like titles and lyrics) by
entering them in UTF-8 encoding, and using a Pango based backend.
Depending on the fonts installed, this fragment will render Bulgarian
(Cyrillic), Hebrew, Japanese and Portuguese.

"
  doctitle = "UTF-8"
}

% end verbatim - this comment is a hack to prevent texinfo.tex
% from choking on non-European UTF-8 subsets

%% Edit this file using a Unicode aware editor, such as GVIM, GEDIT, Emacs

%{

You may have to install additional fonts.

Red Hat Fedora

	linux-libertine-fonts (Latin, Cyrillic, Hebrew)
	ipa-mincho-fonts ipa-gothic-fonts (Japanese)

Debian GNU/Linux, Ubuntu

	fonts-linuxlibertine (Latin, Cyrillic, Hebrew)
	fonts-ipafont (Japanese)

%}

% Font settings for Cyrillic and Hebrew
% Linux Libertine fonts contain Cyrillic and Hebrew glyphs.
\paper {
  #(define fonts
    (set-global-fonts
     #:roman "Linux Libertine O,serif"
     #:sans "Linux Biolinum O,sans-serif"
     #:typewriter "Linux Libertine Mono O,monospace"
   ))
}

% Cyrillic font
bulgarian = \lyricmode {
  Жълтата дюля беше щастлива, че пухът, който цъфна, замръзна като гьон.
}

hebrew = \lyricmode {
  זה כיף סתם לשמוע איך תנצח קרפד עץ טוב בגן.
}

japanese = \lyricmode {
  いろはにほへど ちりぬるを
  わがよたれぞ  つねならむ
  うゐのおくや  まけふこえて
  あさきゆめみじ ゑひもせず
}

% "a legal song to you"
portuguese = \lyricmode {
  à vo -- cê uma can -- ção legal
}

\relative c' {
  c2 d
  e2 f
  g2 f
  e1
}
\addlyrics { \bulgarian }
\addlyrics { \hebrew }
\addlyrics { \japanese }
\addlyrics { \portuguese }
