# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


import sys

from PyQt4.uic.properties import Properties
from PyQt4.uic.uiparser import UIParser
from PyQt4.uic.Compiler import qtproxies
from PyQt4.uic.Compiler.indenter import createCodeIndenter, getIndenter, \
        write_code
from PyQt4.uic.Compiler.qobjectcreator import CompilerCreatorPolicy
from PyQt4.uic.Compiler.misc import write_import


class UICompiler(UIParser):
    def __init__(self):
        UIParser.__init__(self, qtproxies.QtCore, qtproxies.QtGui,
                CompilerCreatorPolicy())

    def reset(self):
        qtproxies.i18n_strings = []
        UIParser.reset(self)

    def setContext(self, context):
        qtproxies.i18n_context = context

    def createToplevelWidget(self, classname, widgetname):
        indenter = getIndenter()
        indenter.level = 0

        indenter.write("from PyQt4 import QtCore, QtGui")
        indenter.write("")

        indenter.write("try:")
        indenter.indent()
        indenter.write("_fromUtf8 = QtCore.QString.fromUtf8")
        indenter.dedent()
        indenter.write("except AttributeError:")
        indenter.indent()
        indenter.write("_fromUtf8 = lambda s: s")
        indenter.dedent()
        indenter.write("")

        indenter.write("class Ui_%s(object):" % self.uiname)
        indenter.indent()
        indenter.write("def setupUi(self, %s):" % widgetname)
        indenter.indent()
        w = self.factory.createQObject(classname, widgetname, (),
                                   is_attribute = False,
                                   no_instantiation = True)
        w.baseclass = classname
        w.uiclass = "Ui_%s" % self.uiname
        return w

    def setDelayedProps(self):
        write_code("")
        write_code("self.retranslateUi(%s)" % self.toplevelWidget)
        UIParser.setDelayedProps(self)

    def finalize(self):
        indenter = getIndenter()
        indenter.level = 1
        indenter.write("")
        indenter.write("def retranslateUi(self, %s):" % self.toplevelWidget)
        indenter.indent()

        if qtproxies.i18n_strings:
            for s in qtproxies.i18n_strings:
                indenter.write(s)
        else:
            indenter.write("pass")

        indenter.dedent()
        indenter.dedent()

        # Make a copy of the resource modules to import because the parser will
        # reset() before returning.
        self._resources = self.resources

    def compileUi(self, input_stream, output_stream, from_imports):
        createCodeIndenter(output_stream)
        w = self.parse(input_stream)

        indenter = getIndenter()
        indenter.write("")

        self.factory._cpolicy._writeOutImports()

        for res in self._resources:
            write_import(res, from_imports)

        return {"widgetname": str(w),
                "uiclass" : w.uiclass,
                "baseclass" : w.baseclass}
