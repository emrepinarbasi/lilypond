\header {
texidoc="LilyPond 1.3 is more flexible than some users realise.  Han-Wen could be very rich.
";
}

% Btw, I've leant an el-neato trick for formatting code in email messages,
% using inderect buffers.
%
% M-x make-indirect-buffer RET RET foo RET C-x b foo RET
% Select region and then narrow: C-x n n
% Set mode, eg: M-x sch TAB RET
%

%{
    I've just entered a request on cosource.com :

        http://www.cosource.com/cgi-bin/cos.pl/wish/info/387
 
    Here's a copy of my feature request :
 
        Your task, if you accept it is to implement a \smarttranspose
        command> that would translate such oddities into more natural
        notations. Double accidentals should be removed, as well as #E
        (-> F), bC (-> B), bF (-> E), #B (-> C).

You mean like this. (Sorry 'bout the nuked indentation.)

Add IMPLEMENT_TYPE_P(Music, "music?"); to music.cc, and presto, done.

That's an easy $ 100; if I'd make $ 200/hour for every hour I worked
on Lily, I'd be very rich :)

%}

#(define  (unhair-pitch p)
  (let* ((o (pitch-octave p))
         (a (pitch-alteration p))
	 (n (pitch-notename p)))

    (cond
     ((and (> a 0) (or (eq? n 6) (eq? n 2)))
      (set! a (- a 1)) (set! n (+ n 1)))
     ((and (< a 0) (or (eq? n 0) (eq? n 3)))
      (set! a (+ a 1)) (set! n (- n 1))))
    
    (cond
     ((eq? a 2)  (set! a 0) (set! n (+ n 1)))
     ((eq? a -2) (set! a 0) (set! n (- n 1))))

    (if (< n 0) (begin (set!  o (- o 1)) (set! n (+ n 7))))
    (if (> n 7) (begin (set!  o (+ o 1)) (set! n (- n 7))))
    
    (make-pitch o n a)))

#(define (smart-transpose music pitch)
  (let* ((es (ly-get-mus-property music 'elements))
	 (e (ly-get-mus-property music 'element))
	 (p (ly-get-mus-property music 'pitch))
	 (body (ly-get-mus-property music 'body))
	 (alts (ly-get-mus-property music 'alternatives)))

    (if (pair? es)
	(ly-set-mus-property
	 music 'elements
	 (map (lambda (x) (smart-transpose x pitch)) es)))
    
    (if (music? alts)
	(ly-set-mus-property
	 music 'alternatives
	 (smart-transpose alts pitch)))
    
    (if (music? body)
	(ly-set-mus-property
	 music 'body
	 (smart-transpose body pitch)))

    (if (music? e)
	(ly-set-mus-property
	 music 'element
	 (smart-transpose e pitch)))
    
    (if (pitch? p)
	(begin
	  (set! p (unhair-pitch (Pitch::transpose p pitch)))
	  (ly-set-mus-property music 'pitch p)))
    
    music))


music = \notes \relative c' { c4 d  e f g a b  c }

\score {
  \notes \context Staff {
    \transpose ais' \music
    \apply #(lambda (x) (smart-transpose x (make-pitch 0 5 1)))
      \music
  }
  \paper { linewidth = -1.; }
}
