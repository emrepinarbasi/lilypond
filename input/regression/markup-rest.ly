\version "2.21.0"

\header {
  texidoc = "The rest markup function works for a variety of style, dot and
duration settings."
}

showSimpleRest =
#(define-scheme-function (dots) (string?)
   (make-override-markup
     (cons 'baseline-skip 7)
     (make-column-markup
       (map
         (lambda (style)
                 (make-line-markup
                   (list
                     (make-pad-to-box-markup
                       '(0 . 20) '(0 . 0)
                        (symbol->string style))
                     (make-override-markup
                       (cons 'line-width 60)
                       (make-override-markup
                         (cons 'style style)
                         (make-fill-line-markup
                           (map
                             (lambda (duration)
                                     (make-rest-markup
                                       (if (string? duration)
                                           duration
                                           (string-append
                                             (number->string (expt 2 duration))
                                             dots))))
                             (append
                               '("maxima" "longa" "breve")
                               (iota 11)))))))))
         '(default
           mensural
           neomensural
           classical
           baroque
           altdefault
           petrucci
           blackpetrucci
           semipetrucci
           kievan)))))

showMultiMeasureRests =
#(define-scheme-function ()()
   (make-override-markup
     (cons 'baseline-skip 7)
     (make-column-markup
       (map
         (lambda (style)
                 (make-line-markup
                   (list
                     (make-pad-to-box-markup
                        '(0 . 20) '(0 . 0)
                         (symbol->string style))
                     (make-override-markup
                       (cons 'line-width 80)
                       (make-override-markup
                         (cons 'style style)
                         (make-fill-line-markup
                           (map
                             (lambda (duration)
                               (make-line-markup
                                 (list
                                   (make-override-markup
                                      (cons 'multi-measure-rest #t)
                                      (make-rest-markup
                                         (number->string duration))))))
                             (cdr (iota 13)))))))))
         '(default
           mensural
           neomensural
           classical
           baroque
           altdefault
           petrucci
           blackpetrucci
           semipetrucci
           kievan)))))

\markup \column { \bold "Simple Rests" \combine \null \vspace #0.1 }

\showSimpleRest "."

\markup \column { \combine \null \vspace #0.1 \bold "MultiMeasureRests" \combine \null \vspace #0.1 }

\showMultiMeasureRests
