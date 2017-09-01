'''test by running example scripts
'''
import os
import os.path
import subprocess

import cairo
#import py.test as test


def test_snippets():
  '''Run all snippets in png,pdf,ps,svg mode and check they exit successfully.
  This will create *.{pdf,png,ps,svg} output files in
  examples/cairo_snippets/snippets/
  '''
  def doSnippets(name):
    retcode = subprocess.call('python %s -s' % name, shell=True)
    assert retcode == 0, 'Error: retcode == {0}'.format(retcode)

  os.chdir(os.path.join(os.path.dirname(__file__), '..', 'examples',
                        'cairo_snippets'))
  if cairo.HAS_PDF_SURFACE:
    doSnippets('snippets_pdf.py')
  if cairo.HAS_IMAGE_SURFACE and cairo.HAS_PNG_FUNCTIONS:
    doSnippets('snippets_png.py')
  if cairo.HAS_PS_SURFACE:
    doSnippets('snippets_ps.py')
  if cairo.HAS_SVG_SURFACE:
    doSnippets('snippets_svg.py')
