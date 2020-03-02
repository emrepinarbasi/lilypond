#!@PYTHON@

# Created 01 September 2003 by Heikki Junes.
# Rewritten by John Mandereau

# Generates lilypond-words.el for (X)Emacs and lilypond-words[.vim] for Vim.

import codecs
import re
import sys
import os
import getopt

keywords = []
reserved_words = []
note_names = []

# keywords not otherwise found
keywords += ['include', 'maininput', 'version']

# the main keywords
s = codecs.open ('lily/lily-lexer.cc', 'r', 'utf-8').read ()
keywords += [w for w in re.findall (r"\s*{\"(.+)\",\s*.*},\s*\n", s)]

# markup commands
for name in ['ly/toc-init.ly',
             'scm/define-markup-commands.scm',
             'scm/fret-diagrams.scm',
             'scm/harp-pedals.scm']:
    s = codecs.open (name, 'r', 'utf-8').read ()
    keywords += [w for w in re.findall (r"\(define-markup[a-z-]+\s+\(([a-zA-Z-]+)", s)]

# identifiers and keywords
for name in ['ly/chord-modifiers-init.ly',
             'ly/dynamic-scripts-init.ly',
             'ly/engraver-init.ly',
             'ly/grace-init.ly',
             'ly/gregorian.ly',
             'ly/music-functions-init.ly',
             'ly/performer-init.ly',
             'ly/property-init.ly',
             'ly/scale-definitions-init.ly',
             'ly/script-init.ly',
             'ly/spanners-init.ly',
             'ly/toc-init.ly',
             'ly/declarations-init.ly']:
    s = codecs.open (name, 'r', 'utf-8').read ()
    keywords += [w for w in re.findall (r"(?m)^\s*\"?([a-zA-Z]+)\"?\s*=", s)]

# note names
s = codecs.open ('scm/define-note-names.scm', 'r', 'utf-8').read ()
note_names += [n for n in re.findall (r"(?m)^\s*\(([a-z]+)\s+\.\s+,\(ly:make-pitch", s)]

# reserved words
for name in ['ly/engraver-init.ly',
             'ly/performer-init.ly']:
    s = codecs.open (name, 'r', 'utf-8').read ()
    for pattern in [r"(?m)^\s*.consists\s+\"([a-zA-Z_]+)\"",
                    r"[\\]name\s+[\"]?([a-zA-Z_]+)[\"]?",
                    r"\s+([a-zA-Z_]+)\s*\\(?:set|override)"]:
        reserved_words += [w for w in re.findall (pattern, s)]

keywords = list (set (keywords))
keywords.sort (reverse=True)

reserved_words = list (set (reserved_words))
reserved_words.sort (reverse=True)

note_names = list (set (note_names))
note_names.sort (reverse=True)


# output
outdir = ''
out_words = False
out_el = False
out_vim = False

options = getopt.getopt (sys.argv[1:],
  '', ['words', 'el', 'vim', 'dir='])[0]

for (o, a) in options:
    if o == '--words':
        out_words = True
    elif o == '--el':
        out_el = True
    elif o == '--vim':
        out_vim = True
    elif o == '--dir':
        outdir = a

if out_words or out_el:
    outstring = ''.join (['\\\\' + w + '\n' for w in keywords])
    outstring += ''.join ([w + '\n' for w in reserved_words])
    outstring += ''.join ([w + '\n' for w in note_names])

if out_words:
    f = open (os.path.join (outdir, 'lilypond-words'), 'w')
    f.write (outstring)

if out_el:
    f = open (os.path.join (outdir, 'lilypond-words.el'), 'w')
    f.write (outstring)

    # the menu in lilypond-mode.el
    # for easier typing of this list, replace '/' with '\' below
    # when writing to file
    elisp_menu = ['/( - _ /) -',
                  '/[ - _ /] -',
                  '< - _ > -',
                  '<< - _ >> -',
                  '///( - _ ///) -',
                  '///[ - _ ///] -',
                  '///< - _ ///! -',
                  '///> - _ ///! -',
                  '//center - / << _ >> -',
                  '//column - / << _ >> -',
                  '//context/ Staff/ = - % { _ } -',
                  '//context/ Voice/ = - % { _ } -',
                  '//markup - { _ } -',
                  '//notes - { _ } -',
                  '//relative - % { _ } -',
                  '//score - { //n /? //simultaneous { //n _ //n } /! //n //layout {  } //n /? //midi {  } //n /! } //n -',
                  '//simultaneous - { _ } -',
                  '//sustainOn - _ //sustainOff -',
                  '//times - % { _ } -',
                  '//transpose - % { _ } -',
                  '']
    f.write ('\n'.join ([line.replace ('/', '\\') for line in elisp_menu]))

if out_vim:
    f = open (os.path.join (outdir, 'lilypond-words.vim'), 'w')
    f.write ('syn match lilyKeyword \"[-_^]\\?\\\\\\(')
    f.write (''.join ([w + '\\|' for w in keywords]))
    f.write ('n\\)\\(\\A\\|\\n\\)\"me=e-1\n')

    f.write ('syn match lilyReservedWord \"\\(\\A\\|\\n\\)\\(')
    f.write (''.join ([w + '\\|' for w in reserved_words]))
    f.write ('Score\\)\\(\\A\\|\\n\\)\"ms=s+1,me=e-1\n')

    f.write ('syn match lilyNote \"\\<\\(\\(\\(')
    f.write (''.join ([w + '\\|' for w in note_names]))
    f.write ('a\\)\\([,\']\\)\\{,4}\\([?!]\\)\\?\\)\\|s\\|r\\|R\\|q\\)\\(\\(128\\|64\\|32\\|16\\|8\\|4\\|2\\|1\\|\\\\breve\\|\\\\longa\\|\\\\maxima\\)[.]\\{,8}\\)\\?\\(\\A\\|\\n\\)\"me=e-1\n')
