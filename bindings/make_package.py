#!/usr/bin/env python
#
# We'll use distutils to create a distutils script.
# This is distutils inception! :)
#

from distutils.core import Extension, setup
from glob import glob
from os import chdir, chmod, unlink
from os.path import dirname, exists, join
from shutil import copyfile

# Hardcode the command line.
import sys
sys.argv = [sys.argv[0], 'sdist']

# Chdir to the directory of the script.
chdir(dirname(__file__))

# Get the sources from the manifest file.
with open('MANIFEST', 'rU') as fd:
    manifest = [x.strip() for x in fd.readlines()]
sources = [x for x in manifest if x.endswith('.cpp')]
sources.append('otpnitro.i')
to_copy = [x for x in manifest if x.endswith('.h') or x.endswith('.cpp')]
to_copy.append('README')

try:

    # Overwrite setup.py with the list of sources.
    with open('setup.py', 'w') as fd:
        fd.write(
            """#!/usr/bin/env python

from distutils.core import Extension, setup

sources = %r

setup(name = 'otpnitro',
      version = '1.0',
      description = 'Python wrapper for the otpnitro crypto library',
      author = 'capi_x',
      author_email = 'capi_x@haibane.org',
      url = 'http://www.haibane.org/',
      py_modules = ['otpnitro'],
      ext_modules = [Extension(name='_otpnitro',
                               sources=sources,
                               swig_opts=['-c++', '-I.'],
                               include_dirs=['.'])],
     )""" % sources)
    chmod('setup.py', 0o755)

    # Delete any previously copied sources.
    for filename in to_copy:
        if exists(filename):
            unlink(filename)

    # Copy the sources to the current directory.
    # Otherwise distutils can't find them.
    for dst in to_copy:
        src = join('..', dst)
        if not exists(dst) and exists(src):
            copyfile(src, dst)

    # Run distutils.
    setup(name = 'otpnitro',
          version = '1.0',
          description = 'Python wrapper for the otpnitro crypto library',
          author = 'capi_x',
          author_email = 'capi_x@haibane.org',
          url = 'http://www.haibane.org/',
          py_modules = ['otpnitro'],
          ext_modules = [Extension(name='_otpnitro',
                                   sources=sources,
                                   swig_opts=['-c++', '-I.'],
                                   include_dirs=['.'])],
         )

finally:

    # Delete setup.py.
    if exists('setup.py'):
        unlink('setup.py')

    # Delete the copied sources.
    for filename in to_copy:
        if exists(filename):
            unlink(filename)

