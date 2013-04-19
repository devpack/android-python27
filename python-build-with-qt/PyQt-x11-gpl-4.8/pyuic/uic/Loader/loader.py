# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


import os.path

from PyQt4 import QtGui, QtCore
from PyQt4.uic.uiparser import UIParser
from PyQt4.uic.Loader.qobjectcreator import LoaderCreatorPolicy


class DynamicUILoader(UIParser):
    def __init__(self):
        UIParser.__init__(self, QtCore, QtGui, LoaderCreatorPolicy())

    def createToplevelWidget(self, classname, widgetname):
        if self.toplevelInst is not None:
            if not isinstance(self.toplevelInst, self.factory.findQObjectType(classname)):
                raise TypeError(("Wrong base class of toplevel widget",
                                  (type(self.toplevelInst), classname)))
            return self.toplevelInst
        else:
            return self.factory.createQObject(classname, widgetname, ())

    def loadUi(self, filename, toplevelInst=None):
        self.toplevelInst = toplevelInst

        # Allow the filename to be a QString.
        filename = str(filename)

        return self.parse(filename, os.path.dirname(filename))
