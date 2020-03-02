#!@PYTHON@
# mass-link.py

# USAGE:  mass-link.py  [--prepend-suffix SUFFIX]   symbolic | hard   SOURCEDIR DESTDIR FILES
#
# create hard or symbolic links to SOURCEDIR/FILES in DESTDIR
#
# If symbolic or hard links are not provided by the operating system,
# copies will be made instead.  However, if the operating system
# support symbolic or hard links, then this program expects to
# operate on a filesystem which supports them too.
#
# If --prepend-suffix is specified, link to foo.bar will be called
# fooSUFFIX.bar.  Shell wildcards expansion is performed on FILES.
#
# No check is performed on FILES type; in particular, if FILES
# expansions contain a directory and hard links are requested,
# this program may fail non-gracefully.
#
# Attempts to make hard links across different filesystems are
# caught and replaced by copies.

import sys
import os
import glob
import getopt
import shutil

optlist, args = getopt.getopt (sys.argv[1:], '', ['prepend-suffix='])
link_type, source_dir, dest_dir = args[0:3]
files = args[3:]

source_dir = os.path.normpath (source_dir)
dest_dir = os.path.normpath (dest_dir)

prepended_suffix = ''
for x in optlist:
    if x[0] == '--prepend-suffix':
        prepended_suffix = x[1]

if prepended_suffix:
    def insert_suffix (p):
        l = p.split ('.')
        if len (l) >= 2:
            l[-2] += prepended_suffix
            return '.'.join (l)
        return p + prepended_suffix
else:
    insert_suffix = lambda p: p

if link_type == 'symbolic':
    if hasattr (os, 'symlink'):
        link = os.symlink
    else:
        link = shutil.copy
elif link_type == 'hard':
    if hasattr (os, 'link'):
        link = os.link
    else:
        link = shutil.copy
else:
    sys.stderr.write(sys.argv[0] + ': ' + link_type + ": wrong argument, expected 'symbolic' or 'hard'\n")
    sys.exit (1)

sourcefiles = []
for pattern in files:
    sourcefiles += (glob.glob (os.path.join (source_dir, pattern)))

def relative_path (f):
    if source_dir == '.':
        return f
    return f[len (source_dir) + 1:]

destfiles = [os.path.join (dest_dir, insert_suffix (relative_path (f))) for f in sourcefiles]

destdirs = set ([os.path.dirname (dest) for dest in destfiles])
[os.makedirs (d) for d in destdirs if not os.path.exists (d)]

def force_link (src,dest):
    if os.path.exists (dest):
        os.remove (dest)
    try:
        link (src, dest)
    except OSError as e:
        if e.errno == 18:
            shutil.copy (src, dest)
        else:
            raise
    os.utime (dest, None)

list(map (force_link, sourcefiles, destfiles))
