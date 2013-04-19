# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


__all__ = ("compileUi", "compileUiDir", "loadUiType", "loadUi", "widgetPluginPath")

from PyQt4.uic.Compiler import indenter, compiler


_header = """# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '%s'
#
# Created: %s
#      by: PyQt4 UI code generator %s
#
# WARNING! All changes made in this file will be lost!

"""


_pyqt3_wrapper_code = """
class %(widgetname)s(QtGui.%(baseclass)s, %(uiclass)s):
\tdef __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
\t\tQtGui.%(baseclass)s.__init__(self, parent, f)

\t\tself.setupUi(self)
"""


_display_code = """
if __name__ == "__main__":
\timport sys
\tapp = QtGui.QApplication(sys.argv)
\t%(widgetname)s = QtGui.%(baseclass)s()
\tui = %(uiclass)s()
\tui.setupUi(%(widgetname)s)
\t%(widgetname)s.show()
\tsys.exit(app.exec_())
"""


def compileUiDir(dir, recurse=False, map=None, **compileUi_args):
    """compileUiDir(dir, recurse=False, map=None, **compileUi_args)

    Creates Python modules from Qt Designer .ui files in a directory or
    directory tree.

    dir is the name of the directory to scan for files whose name ends with
    '.ui'.  By default the generated Python module is created in the same
    directory ending with '.py'.
    recurse is set if any sub-directories should be scanned.  The default is
    False.
    map is an optional callable that is passed the name of the directory
    containing the '.ui' file and the name of the Python module that will be
    created.  The callable should return a tuple of the name of the directory
    in which the Python module will be created and the (possibly modified)
    name of the module.  The default is None.
    compileUi_args are any additional keyword arguments that are passed to
    the compileUi() function that is called to create each Python module.
    """

    import os

    # Compile a single .ui file.
    def compile_ui(ui_dir, ui_file):
        # Ignore if it doesn't seem to be a .ui file.
        if ui_file.endswith('.ui'):
            py_dir = ui_dir
            py_file = ui_file[:-3] + '.py'

            # Allow the caller to change the name of the .py file or generate
            # it in a different directory.
            if map is not None:
                py_dir, py_file = map(py_dir, py_file)

            # Make sure the destination directory exists.
            try:
                os.makedirs(py_dir)
            except:
                pass

            ui_path = os.path.join(ui_dir, ui_file)
            py_path = os.path.join(py_dir, py_file)

            ui_file = open(ui_path, 'r')
            py_file = open(py_path, 'w')

            try:
                compileUi(ui_file, py_file, **compileUi_args)
            finally:
                ui_file.close()
                py_file.close()

    if recurse:
        for root, _, files in os.walk(dir):
            for ui in files:
                compile_ui(root, ui)
    else:
        for ui in os.listdir(dir):
            if os.path.isfile(os.path.join(dir, ui)):
                compile_ui(dir, ui)


def compileUi(uifile, pyfile, execute=False, indent=4, pyqt3_wrapper=False, from_imports=False):
    """compileUi(uifile, pyfile, execute=False, indent=4, pyqt3_wrapper=False, from_imports=False)

    Creates a Python module from a Qt Designer .ui file.
    
    uifile is a file name or file-like object containing the .ui file.
    pyfile is the file-like object to which the Python code will be written to.
    execute is optionally set to generate extra Python code that allows the
    code to be run as a standalone application.  The default is False.
    indent is the optional indentation width using spaces.  If it is 0 then a
    tab is used.  The default is 4.
    pyqt3_wrapper is optionally set to generate extra code that allows the code
    to be used as it would be with PyQt v3.
    from_imports is optionally set to generate import statements that are
    relative to '.'.
    """

    from time import ctime
    from PyQt4.QtCore import PYQT_VERSION_STR

    try:
        uifname = uifile.name
    except AttributeError:
        uifname = uifile

    indenter.indentwidth = indent

    pyfile.write(_header % (uifname, ctime(), PYQT_VERSION_STR))

    winfo = compiler.UICompiler().compileUi(uifile, pyfile, from_imports)

    if pyqt3_wrapper:
        indenter.write_code(_pyqt3_wrapper_code % winfo)

    if execute:
        indenter.write_code(_display_code % winfo)


def loadUiType(uifile, from_imports=False):
    """loadUiType(uifile) -> (form class, base class)

    Load a Qt Designer .ui file and return the generated form class and the Qt
    base class.

    uifile is a file name or file-like object containing the .ui file.
    from_imports is optionally set to use import statements that are relative
    to '.'.
    """

    import sys

    from PyQt4 import QtGui

    if sys.hexversion >= 0x03000000:
        from PyQt4.uic.port_v3.string_io import StringIO
    else:
        from PyQt4.uic.port_v2.string_io import StringIO

    code_string = StringIO()
    winfo = compiler.UICompiler().compileUi(uifile, code_string, from_imports)

    ui_globals = {}
    exec(code_string.getvalue(), ui_globals)

    return (ui_globals[winfo["uiclass"]], getattr(QtGui, winfo["baseclass"]))


def loadUi(uifile, baseinstance=None):
    """loadUi(uifile, baseinstance=None) -> widget

    Load a Qt Designer .ui file and return an instance of the user interface.

    uifile is a file name or file-like object containing the .ui file.
    baseinstance is an optional instance of the Qt base class.  If specified
    then the user interface is created in it.  Otherwise a new instance of the
    base class is automatically created.
    """

    from PyQt4.uic.Loader.loader import DynamicUILoader

    return DynamicUILoader().loadUi(uifile, baseinstance)


# The list of directories that are searched for widget plugins.
from PyQt4.uic.objcreator import widgetPluginPath
