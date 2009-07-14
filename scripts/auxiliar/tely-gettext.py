#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Temporary script that helps translated docs sources conversion
# for texi2html processing

# USAGE:  tely-gettext.py LANG FILES

print "tely-gettext.py"

import sys
import re
import os

import langdefs

lang = sys.argv[1]
files = sys.argv[2:]

double_punct_char_separator = langdefs.LANGDICT[lang].double_punct_char_sep
_doc = langdefs.translation[lang]

include_re = re.compile (r'@include (.*?)$', re.M)
whitespaces = re.compile (r'\s+')
ref_re = re.compile (r'(?ms)@(ruser|rprogram|ref|rlearning)\{(.*?)\}')
node_section_re = re.compile (r'@node (.*?)\n@((?:unnumbered|appendix)(?:(?:sub){0,2}sec)?|top|chapter|(?:sub){0,2}section|(?:major|chap|(?:sub){0,2})heading) (.*?)\n')
menu_entry_re = re.compile (r'\* (.*?)::')
untranslated_node_re = re.compile (r'(@node\s+.*\n@.*\n.*)(\s+@untranslated(.|\n)+?)(?=@node|@subheading|@menu|$)')


def ref_gettext (m):
    r = whitespaces.sub (' ', m.group (2))
    return '@' + m.group (1) + '{' + _doc (r) + '}'

def node_gettext (m):
    return '@node ' + _doc (m.group (1)) + '\n@' + \
        m.group (2) + ' ' + _doc (m.group (3)) + \
       '\n@translationof ' + m.group (1) + '\n'

def menu_entry_gettext (m):
    return '* ' + _doc (m.group (1)) + '::'

def process_file (filename):
    print "Processing %s" % filename
    f = open (filename, 'r')
    page = f.read ()
    f.close()
    page = node_section_re.sub (node_gettext, page)
    page = ref_re.sub (ref_gettext, page)
    page = menu_entry_re.sub (menu_entry_gettext, page)
    page = page.replace ("""@c -- SKELETON FILE --
""", '')
    page = page.replace ('UNTRANSLATED NODE: IGNORE ME', '@untranslated')
    page = untranslated_node_re.sub ('\\1 @c external\\2', page)
    includes = include_re.findall (page)
    f = open (filename, 'w')
    f.write (page)
    f.close ()
    dir = os.path.dirname (filename)
    for file in includes:
        p = os.path.join (dir, file)
        if os.path.exists (p):
            process_file (p)

for filename in files:
    process_file (filename)
