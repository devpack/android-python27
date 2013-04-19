# Copyright (c) 2010 Riverbank Computing Limited.


import sys
import optparse

from PyQt4 import QtCore
from PyQt4.uic.driver import Driver


Version = "Python User Interface Compiler %s for Qt version %s" % (QtCore.PYQT_VERSION_STR, QtCore.QT_VERSION_STR)


if sys.hexversion >= 0x03000000:
    from PyQt4.uic.port_v3.invoke import invoke
else:
    from PyQt4.uic.port_v2.invoke import invoke


parser = optparse.OptionParser(usage="pyuic4 [options] <ui-file>",
        version=Version)
parser.add_option("-p", "--preview", dest="preview", action="store_true",
        default=False,
        help="show a preview of the UI instead of generating code")
parser.add_option("-o", "--output", dest="output", default="-", metavar="FILE",
        help="write generated code to FILE instead of stdout")
parser.add_option("-x", "--execute", dest="execute", action="store_true",
        default=False,
        help="generate extra code to test and display the class")
parser.add_option("-d", "--debug", dest="debug", action="store_true",
        default=False, help="show debug output")
parser.add_option("-i", "--indent", dest="indent", action="store", type="int",
        default=4, metavar="N",
        help="set indent width to N spaces, tab if N is 0 (default: 4)")
parser.add_option("-w", "--pyqt3-wrapper", dest="pyqt3_wrapper",
        action="store_true", default=False,
        help="generate a PyQt v3 style wrapper")

g = optparse.OptionGroup(parser, title="Code generation options")
g.add_option("--from-imports", dest="from_imports", action="store_true",
        default=False, help="generate imports relative to '.'")
parser.add_option_group(g)

opts, args = parser.parse_args()

if len(args) != 1:
    sys.stderr.write("Error: one input ui-file must be specified\n")
    sys.exit(1)

sys.exit(invoke(Driver(opts, args[0])))
