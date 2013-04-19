#!/usr/bin/env python

from __future__ import division
from __future__ import with_statement

import base64
import os
import re
import sys

from PyQt4.QtCore import (PYQT_VERSION_STR, QByteArray, QDir, QEvent,
        QFile, QFileInfo, QIODevice, QPoint, QProcess, QRegExp,
        QSettings, QString, QT_VERSION_STR, QTextStream, QThread,
        QTimer, QUrl, QVariant, Qt, SIGNAL)
from PyQt4.QtGui import (QAction, QApplication, QButtonGroup, QCheckBox,
        QColor, QColorDialog, QComboBox, QCursor, QDesktopServices,
        QDialog, QDialogButtonBox, QFileDialog, QFont, QFontComboBox,
        QFontMetrics, QGridLayout, QHBoxLayout, QIcon, QInputDialog,
        QKeySequence, QLabel, QLineEdit, QListWidget, QMainWindow,
        QMessageBox, QPixmap, QPushButton, QRadioButton,
        QRegExpValidator, QShortcut, QSpinBox, QSplitter,
        QSyntaxHighlighter, QTabWidget, QTextBrowser, QTextCharFormat,
        QTextCursor, QTextDocument, QTextEdit, QToolTip, QVBoxLayout,
        QWidget)


__version__ = "0.9.9"
__license__ = """<font color=green>\
Copyright (c) 2007-9 Mark Summerfield. All rights reserved.</font>

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, version 2 of the License, or version 3 of the
License or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
<i>without any warranty</i>; without even the implied warranty of
<i>merchantability</i> or <i>fitness for a particular purpose</i>. 
See the <a href="http://www.gnu.org/licenses/">GNU General Public
License</a> for more details."""

MAC = "qt_mac_set_native_menubar" in dir()

KEYWORDS = ["and", "as", "assert", "break", "class", "continue", "def",
        "del", "elif", "else", "except", "exec", "finally", "for", "from",
        "global", "if", "import", "in", "is", "lambda", "not", "or",
        "pass", "print", "raise", "return", "try", "while", "with",
        "yield"]

BUILTINS = ["abs", "all", "any", "basestring", "bool", "callable", "chr",
        "classmethod", "cmp", "compile", "complex", "delattr", "dict",
        "dir", "divmod", "enumerate", "eval", "execfile", "exit", "file",
        "filter", "float", "frozenset", "getattr", "globals", "hasattr",
        "hex", "id", "int", "isinstance", "issubclass", "iter", "len",
        "list", "locals", "long", "map", "max", "min", "object", "oct",
        "open", "ord", "pow", "property", "range", "reduce", "repr",
        "reversed", "round", "set", "setattr", "slice", "sorted",
        "staticmethod", "str", "sum", "super", "tuple", "type", "unichr",
        "unicode", "vars", "xrange", "zip"] 

CONSTANTS = ["False", "True", "None", "NotImplemented", "Ellipsis"]

MODULES = dict([(key, False) for key in ("array", "bisect", "bsddb",
        "bz2", "codecs", "collections", "copy", "datetime", "decimal",
        "functools", "getopt", "gzip", "heapq", "itertools", "math",
        "optparse", "os", "os.path", "pickle", "cPickle", "random",
        "re", "string", "StringIO", "cStringIO", "struct", "subprocess",
        "sys", "tarfile", "time", "unicodedata", "weakref", "zipfile",
        "QAxContainer", "QtAssistant", "QtCore", "QtDesigner", "QtGui",
        "QtNetwork", "QtOpenGL", "QtSql", "QtSvg", "QtTest", "QtXml")])

TIMEOUT = 5000
ICONS = {}
PIXMAPS = {}
Config = {}
CAT = {} # Completions And Tooltips
MIN_COMPLETION_LEN = 3
MAX_TOOLTIP_LEN = 1000
FROM_IMPORT_RE = re.compile(r"from\s+([\w.]+)\s+import\s+(.*)")
WORDS = set()
WORD_RE = re.compile(r"[\W+.]")
MIN_WORD_LEN = 3
MAX_WORD_LEN = 64
CATABLE_LINE_RE = QRegExp(r"\b(?:import|def|class)\s+")
CLASS_OR_DEF_RE = re.compile(r"(class|def) ([^\W(:]+)[:(]")


def trimQString(qstr, trimText):
    while qstr.startsWith(trimText):
        qstr = qstr.mid(len(trimText))
    while qstr.endsWith(trimText):
        qstr.chop(len(trimText))
    return qstr


def loadConfig():
    def setDefaultString(name, default):
        value = settings.value(name).toString()
        if value.isEmpty():
            value = default
        Config[name] = value

    settings = QSettings()
    for name in ("window", "shell"):
        Config["%swidth" % name] = settings.value("%swidth" % name,
                QVariant(QApplication.desktop()
                         .availableGeometry().width() / 2)).toInt()[0]
        Config["%sheight" % name] = settings.value("%sheight" % name,
                QVariant(QApplication.desktop()
                         .availableGeometry().height() / 2)).toInt()[0]
        Config["%sy" % name] = settings.value("%sy" % name,
                QVariant(0)).toInt()[0]
    Config["toolbars"] = settings.value("toolbars").toByteArray()
    Config["splitter"] = settings.value("splitter").toByteArray()
    Config["shellx"] = settings.value("shellx",
                                      QVariant(0)).toInt()[0]
    Config["windowx"] = settings.value("windowx",
            QVariant(QApplication.desktop()
                            .availableGeometry().width() / 2)).toInt()[0]
    Config["remembergeometry"] = settings.value("remembergeometry",
            QVariant(True)).toBool()
    Config["startwithshell"] = settings.value("startwithshell",
            QVariant(True)).toBool()
    Config["showwindowinfo"] = settings.value("showwindowinfo",
            QVariant(True)).toBool()
    setDefaultString("shellstartup", """\
from __future__ import division
import codecs
import sys
sys.stdin = codecs.getreader("UTF8")(sys.stdin)
sys.stdout = codecs.getwriter("UTF8")(sys.stdout)""")
    setDefaultString("newfile", """\
#!/usr/bin/env python

from __future__ import division

import sys
""")
    Config["backupsuffix"] = settings.value("backupsuffix",
            QVariant(".bak")).toString()
    setDefaultString("beforeinput", "#>>>")
    setDefaultString("beforeoutput", "#---")
    Config["cwd"] = settings.value("cwd", QVariant(".")).toString()
    Config["tooltipsize"] = settings.value("tooltipsize",
            QVariant(150)).toInt()[0]
    Config["maxlinestoscan"] = settings.value("maxlinestoscan",
            QVariant(5000)).toInt()[0]
    Config["pythondocpath"] = settings.value("pythondocpath", 
            QVariant("http://docs.python.org")).toString()
    Config["autohidefinddialog"] = settings.value("autohidefinddialog",
            QVariant(True)).toBool()
    Config["findcasesensitive"] = settings.value("findcasesensitive",
            QVariant(False)).toBool()
    Config["findwholewords"] = settings.value("findwholewords",
            QVariant(False)).toBool()
    Config["tabwidth"] = settings.value("tabwidth",
            QVariant(4)).toInt()[0]
    Config["fontfamily"] = settings.value("fontfamily",
            QVariant("Bitstream Vera Sans Mono")).toString()
    Config["fontsize"] = settings.value("fontsize",
            QVariant(10)).toInt()[0]
    for name, color, bold, italic in (
            ("normal", "#000000", False, False),
            ("keyword", "#000080", True, False),
            ("builtin", "#0000A0", False, False),
            ("constant", "#0000C0", False, False),
            ("decorator", "#0000E0", False, False),
            ("comment", "#007F00", False, True),
            ("string", "#808000", False, False),
            ("number", "#924900", False, False),
            ("error", "#FF0000", False, False),
            ("pyqt", "#50621A", False, False)):
        Config["%sfontcolor" % name] = settings.value(
                "%sfontcolor" % name, QVariant(color)).toString()
        Config["%sfontbold" % name] = settings.value(
                "%sfontbold" % name, QVariant(bold)).toBool()
        Config["%sfontitalic" % name] = settings.value(
                "%sfontitalic" % name, QVariant(italic)).toBool()


def saveConfig():
    settings = QSettings()
    for key, value in Config.items():
        settings.setValue(key, QVariant(value))


def checkForCAT(line):
    # We can't use CAT to keep track of which modules we have processed.
    # This is because if the user does "import os", one of the names we
    # will get is "os.path", which then goes into CAT; so if later the
    # user did "import os.path", the name "os.path" will already be in
    # CAT (from the "import os") and wouldn't be looked for. So we keep
    # a separate dictionary of modules that we've done in MODULES.
    line = line.strip()
    if line.startswith("import "):
        line = line[len("import "):]
        for mname in [mname.strip() for mname in line.split(",")]:
            if not MODULES.get(mname, False):
                # We have not done this one
                _updateCAT(mname)
    else:
        match = FROM_IMPORT_RE.match(line)
        if match:
            if match.group(1) == "__future__" or not match.group(2):
                return
            for name in [x for x in
                         match.group(2).replace(",", " ").split()]:
                mname = "%s.%s" % (match.group(1), name)
                if not MODULES.get(mname, False):
                    # We have not done this one
                    _updateCAT(mname)
                i = mname.rfind(".")
                while i > -1:
                    mname = mname[:i]
                    if not MODULES.get(mname, False):
                        # We have not done this one
                        _updateCAT(mname)
                    i = mname.rfind(".")
        else:
            for word in WORD_RE.split(line):
                if (not word or
                    len(word) < MIN_WORD_LEN or
                    len(word) > MAX_WORD_LEN or
                    word in CAT or word in WORDS):
                    continue
                WORDS.add(word)


def _updateCAT(mname):
    try:
        MODULES[mname] = True
        CAT.setdefault(mname, {})
        WORDS.discard(mname)
        module = __import__(mname)
        components = []
        if "." in mname:
            for component in mname.split(".")[1:]:
                module = getattr(module, component)
                components.append(component)
        for aname in dir(module):
            if aname.startswith("_"):
                continue
            fullname = "%s.%s" % (mname, aname)
            CAT.setdefault(fullname, "")
            WORDS.discard(fullname)
            CAT.setdefault(aname, "")
            WORDS.discard(aname)
            for component in components:
                CAT.setdefault("%s.%s" % (component, aname), "")
                WORDS.discard("%s.%s" % (component, aname))
            # PyQt4 classes don't have docstrings
            if not mname.startswith(("Qt", "PyQt4")):
                try:
                    tip = eval("sys.modules['%s'].%s.__doc__" % (
                                mname, aname))
                    if tip is not None:
                        tip = (tip[:MAX_TOOLTIP_LEN].strip()
                               .replace("\n\n", "<p>"))
                        CAT[fullname] = tip
                        if CAT[aname] == "":    # First one (i.e., builtin)
                            CAT[aname] = tip    # wins
                        for component in components: # Last one wins
                            CAT["%s.%s" % (component, aname)] = tip
                except:
                    pass
            try:
                for bname in eval("dir(sys.modules['%s'].%s)" % (
                        mname, aname)):
                    if bname.startswith("_"):
                        continue
                    cname = "%s.%s" % (fullname, bname)
                    CAT.setdefault(cname, "")
                    WORDS.discard(cname)
                    # PyQt4 classes don't have docstrings
                    if not mname.startswith(("Qt", "PyQt4")):
                        tip = None
                        try:
                            tip = eval(
                                    "sys.modules['%s'].%s.%s.__doc__" % (
                                    mname, aname, bname))
                        except:
                            pass
                        if tip is None:
                            try:
                                tip = eval(
                                        "sys.modules['%s'].%s.__doc__" % (
                                        mname, aname))
                            except:
                                pass
                        if tip is not None:
                            tip = (tip[:MAX_TOOLTIP_LEN].strip()
                                   .replace("\n\n", "<p>"))
                            CAT[cname] = tip
            except:
                pass
    except:
        pass


class HelpForm(QDialog):

    def __init__(self, parent=None):
        super(HelpForm, self).__init__(parent)
        self.setAttribute(Qt.WA_GroupLeader)
        self.setAttribute(Qt.WA_DeleteOnClose)
        browser = QTextBrowser()
        browser.setOpenExternalLinks(True)
        browser.setHtml( # TODO Improve
u"""
<p>This online help provides a brief introduction to Sandbox's completion
and Find and Replace dialog, followed by some useful online links, and
finishing with a summary of its key bindings. It is well worth pulling
down the menus and seeing what options are available since they are
almost all self-explanatory.
<p>
Word completion is achieved using <b>Ctrl+P</b> or by pressing <b>Tab</b>.
A tooltip will appear when you enter <b>(</b>, if one is available.
Completion and tooltips are available for Python's built-ins, and also for
any module that gets imported, whether as part of the start-up (see the
File\N{RIGHTWARDS ARROW}Configure dialog's At Startup tab), or that are
imported in the Shell, or that are mentioned in import statements in any
files that are opened. (This makes loading a file with lots of imports, or
writing an import command in the shell, take a tiny bit longer than it
would otherwise do.) The completion also tries to include your own
identifiers. Also, classes, methods, and functions are added to the Goto 
menu. The number of lines that are scanned for completions, tooltips, 
and for the Goto menu is specified in the 
File\N{RIGHTWARDS ARROW}Configure dialog's General tab's Max Lines to Scan
spinbox.
<p>
When you click <b>Find</b> or <b>Replace</b> in the Find and Replace
dialog, the action will take place and the dialog will close. You can
then do further finds and replaces using <b>Edit\N{RIGHTWARDS ARROW}Find
Again</b> or <b>Edit\N{RIGHTWARDS ARROW}Replace Again</b> (or using
the keyboard shortcuts shown in the menu). If you prefer to have the
Find and Replace dialog visible and use its buttons instead, go to the
File\N{RIGHTWARDS ARROW}Configure dialog's General tab, and uncheck
Automatically Hide the Find and Replace dialog.
<p>
Some useful online documentation links:
<ul>
<li><a href="http://docs.python.org/">Python Documentation</a>
<li><a href="http://www.riverbankcomputing.com/Docs/PyQt4/pyqt4ref.html">
PyQt4 Documentation</a>
<li><a
href="http://www.riverbankcomputing.com/Docs/PyQt4/html/classes.html">
PyQt4 Classes' Documentation</a>
<li><a href="http://aspn.activestate.com/ASPN/Python/Cookbook/">Python
Cookbook</a>
</ul>
<p>
Key bindings:
<ul>
<li><b>\N{UPWARDS ARROW}</b> Move the cursor up one line
<li><b>Ctrl+\N{UPWARDS ARROW}</b> In the shell, copy the previous command
from the command history to the input window. In editor windows, move to
the previous line in the line history.
<li><b>\N{DOWNWARDS ARROW}</b> Move the cursor down one line
<li><b>Ctrl+\N{DOWNWARDS ARROW}</b> In the shell, copy the next command
from the command history to the input window. In editor windows, move to
the next line in the line history.
<li><b>\N{LEFTWARDS ARROW}</b> Move the cursor left one character
<li><b>Ctrl+\N{LEFTWARDS ARROW}</b> Move the cursor left one word
<li><b>\N{RIGHTWARDS ARROW}</b> Move the cursor right one character
<li><b>Ctrl+\N{RIGHTWARDS ARROW}</b> Move the cursor right one word
<li><b>Ctrl+]</b> Indent the selected text (or the current line) by %d
spaces
<li><b>Ctrl+[</b> Unindent the selected text (or the current line) by %d
spaces
<li><b>Ctrl+A</b> Select all the text
<li><b>Backspace</b> Delete the character to the left of the cursor
<li><b>Ctrl+C</b> Copy the selected text to the clipboard
<li><b>Delete</b> Delete the character to the right of the cursor
<li><b>End</b> Move the cursor to the end of the line
<li><b>Ctrl+End</b> Move the cursor to the end of the file
<li><b>Ctrl+Enter</b> Execute the input window's code, or execute the
current file. If executing a file and it is a console application, the
output is shown in a separate window which can be closed by pressing
<b>Esc</b>. (This is the same as pressing <b>F5</b>.)
<li><b>Ctrl+F</b> Pop up the Find and Replace dialog
<li><b>F3</b> Find the next occurrence of the find text; if there is none,
pop up the Find and Replace dialog.
<li><b>Shift+F3</b> Find the next occurrence of word at the cursor; the
search is case sensitive and whole words only.
<li><b>F5</b> Execute the input window's code, or execute the current
file. If executing a file and it is a console application, the
output is shown in a separate window which can be closed by pressing
<b>Esc</b>. (This is the same as pressing <b>Ctrl+Enter</b>.)
<li><b>Ctrl+H</b> Launch Python's documentation in a web browser
<li><b>Home</b> Move the cursor to the beginning of the line
<li><b>Ctrl+Home</b> Move the cursor to the beginning of the file
<li><b>Ctrl+K</b> Delete to the end of the line
<li><b>Ctrl+L</b> Pop up the Goto Line dialog
<li><b>Ctrl+M</b> Go to the matching ([{&lt; or &gt;}]). The matcher looks
at the character preceding the cursor, and if it is a match character the
cursor moves so that the matched character precedes the cursor. If no
suitable character is preceding the cursor, but there is a suitable
character following the cursor, the cursor will advance one character (so
that the match character now precedes it), and works as just described.
(In other words the matching is after\N{LEFT RIGHT ARROW}after.)
<li><b>Ctrl+N</b> Open a new editor window
<li><b>Ctrl+O</b> Open a file open dialog to open a Python file
<li><b>Ctrl+Shift+O</b> Open the file at the cursor. This works for 
<tt>import</tt> statements since Sandbox is smart enough to look for
foo.py if the cursor is on foo. It also works for standard modules, because
if foo.py is not found in the current file's directory, <tt>sys.path</tt>
is searched.
<li><b>Ctrl+P</b> and <b>Tab</b> Pop up a list of possible completions for
the current word. Use the up and down arrow keys and the page up and page
up keys (or the mouse) to navigate; click <b>Enter</b> to accept a
completion or <b>Esc</b> to cancel.
<li><b>PageUp</b> Move up one screen
<li><b>PageDown</b> Move down one screen
<li><b>Ctrl+Q</b> Terminate Sandbox; prompting to save any unsaved changes
for every editor window for which this is necessary. If the user cancels
any save unsaved changes message box, Sandbox will not terminate.
<li><b>Ctrl+R</b> Replace the next occurrence of the find text; if there is
none, pop up the Find and Replace dialog.
<li><b>Ctrl+S</b> Save the current file
<li><b>Ctrl+V</b> Paste the clipboard's text
<li><b>Ctrl+W</b> Close the current file; prompting to save any unsaved
changes if necessary
<li><b>Ctrl+X</b> Cut the selected text to the clipboard
<li><b>Ctrl+Z</b> Undo the last editing action
<li><b>Ctrl+Shift+Z</b> Redo the last editing action
</ul>
Hold down <b>Shift</b> when pressing movement keys to select the text moved
over.
<br>
Press <b>Esc</b> to close this window.
""" % (Config["tabwidth"], Config["tabwidth"]))
        layout = QVBoxLayout()
        layout.setMargin(0)
        layout.addWidget(browser)
        self.setLayout(layout)
        self.resize(500, 500)
        QShortcut(QKeySequence("Escape"), self, self.close)
        self.setWindowTitle("Sandbox - Help")


class FindForm(QDialog):

    def __init__(self, parent=None):
        super(FindForm, self).__init__(parent)

        self.findEdit = QComboBox()
        self.findEdit.setDuplicatesEnabled(False)
        self.findEdit.setEditable(True)
        findLabel = QLabel("Find wha&t:")
        findLabel.setBuddy(self.findEdit)
        self.replaceEdit = QComboBox()
        self.replaceEdit.setDuplicatesEnabled(False)
        self.replaceEdit.setEditable(True)
        replaceLabel = QLabel("Replace w&ith:")
        replaceLabel.setBuddy(self.replaceEdit)
        self.caseSensitiveCheckBox = QCheckBox("&Case sensitive")
        self.caseSensitiveCheckBox.setChecked(Config["findcasesensitive"])
        self.wholeWordsCheckBox = QCheckBox("&Whole words only")
        self.wholeWordsCheckBox.setChecked(Config["findwholewords"])
        buttonBox = QDialogButtonBox()
        self.findButton = buttonBox.addButton("&Find",
                QDialogButtonBox.ActionRole)
        self.replaceButton = buttonBox.addButton("&Replace",
                QDialogButtonBox.ActionRole)
        buttonBox.addButton(QDialogButtonBox.Close)
        if not MAC:
            self.caseSensitiveCheckBox.setFocusPolicy(Qt.NoFocus)
            self.wholeWordsCheckBox.setFocusPolicy(Qt.NoFocus)
            buttonBox.setFocusPolicy(Qt.NoFocus)

        grid = QGridLayout()
        grid.addWidget(findLabel, 0, 0)
        grid.addWidget(self.findEdit, 0, 1)
        grid.addWidget(replaceLabel, 1, 0)
        grid.addWidget(self.replaceEdit, 1, 1)
        layout = QVBoxLayout()
        layout.addLayout(grid)
        hbox = QHBoxLayout()
        hbox.addWidget(self.caseSensitiveCheckBox)
        hbox.addWidget(self.wholeWordsCheckBox)
        hbox.addStretch()
        layout.addLayout(hbox)
        layout.addWidget(buttonBox)
        self.setLayout(layout)

        self.connect(self.findEdit,
                SIGNAL("editTextChanged(QString)"), self.updateUi)
        self.connect(self.findButton, SIGNAL("clicked()"),
                     self.findClicked)
        self.connect(self.replaceButton, SIGNAL("clicked()"),
                     self.replaceClicked)
        self.connect(buttonBox, SIGNAL("rejected()"), self.reject)

        self.updateUi()
        self.setWindowTitle("Sandbox - Find and Replace")


    def findClicked(self):
        self.emit(SIGNAL("find"), self.findEdit.currentText(),
                self.caseSensitiveCheckBox.isChecked(),
                self.wholeWordsCheckBox.isChecked())
        if Config["autohidefinddialog"]:
            self.hide()
        
        
    def replaceClicked(self):
        self.emit(SIGNAL("replace"), self.findEdit.currentText(),
                self.replaceEdit.currentText(),
                self.caseSensitiveCheckBox.isChecked(),
                self.wholeWordsCheckBox.isChecked())
        if Config["autohidefinddialog"]:
            self.hide()
        

    def updateUi(self):
        enable = not self.findEdit.currentText().isEmpty()
        self.findButton.setEnabled(enable)
        self.replaceButton.setEnabled(enable)


class PythonHighlighter(QSyntaxHighlighter):

    Rules = []
    Formats = {}

    def __init__(self, parent=None):
        super(PythonHighlighter, self).__init__(parent)

        self.initializeFormats()

        PythonHighlighter.Rules.append((QRegExp(
                "|".join([r"\b%s\b" % keyword for keyword in KEYWORDS])),
                "keyword"))
        PythonHighlighter.Rules.append((QRegExp(
                "|".join([r"\b%s\b" % builtin for builtin in BUILTINS])),
                "builtin"))
        PythonHighlighter.Rules.append((QRegExp(
                "|".join([r"\b%s\b" % constant
                for constant in CONSTANTS])), "constant"))
        PythonHighlighter.Rules.append((QRegExp(
                r"\b[+-]?[0-9]+[lL]?\b"
                r"|\b[+-]?0[xX][0-9A-Fa-f]+[lL]?\b"
                r"|\b[+-]?[0-9]+(?:\.[0-9]+)?(?:[eE][+-]?[0-9]+)?\b"),
                "number"))
        PythonHighlighter.Rules.append((QRegExp(
                r"\bPyQt4\b|\bQt?[A-Z][a-z]\w+\b"), "pyqt"))
        PythonHighlighter.Rules.append((QRegExp(r"\b@\w+\b"),
                "decorator"))
        stringRe = QRegExp(r"""(?:'[^']*'|"[^"]*")""")
        stringRe.setMinimal(True)
        PythonHighlighter.Rules.append((stringRe, "string"))
        self.stringRe = QRegExp(r"""(:?"["]".*"["]"|'''.*''')""")
        self.stringRe.setMinimal(True)
        PythonHighlighter.Rules.append((self.stringRe, "string"))
        self.tripleSingleRe = QRegExp(r"""'''(?!")""")
        self.tripleDoubleRe = QRegExp(r'''"""(?!')''')


    @staticmethod
    def initializeFormats():
        baseFormat = QTextCharFormat()
        baseFormat.setFontFamily(Config["fontfamily"])
        baseFormat.setFontPointSize(Config["fontsize"])
        for name in ("normal", "keyword", "builtin", "constant",
                "decorator", "comment", "string", "number", "error",
                "pyqt"):
            format = QTextCharFormat(baseFormat)
            format.setForeground(
                            QColor(Config["%sfontcolor" % name]))
            if Config["%sfontbold" % name]:
                format.setFontWeight(QFont.Bold)
            format.setFontItalic(Config["%sfontitalic" % name])
            PythonHighlighter.Formats[name] = format


    def highlightBlock(self, text):
        NORMAL, TRIPLESINGLE, TRIPLEDOUBLE, ERROR = range(4)

        textLength = text.length()
        prevState = self.previousBlockState()

        self.setFormat(0, textLength,
                       PythonHighlighter.Formats["normal"])

        if text.startsWith("Traceback") or text.startsWith("Error: "):
            self.setCurrentBlockState(ERROR)
            self.setFormat(0, textLength,
                           PythonHighlighter.Formats["error"])
            return
        if (prevState == ERROR and
            not (text.startsWith(sys.ps1) or text.startsWith("#"))):
            self.setCurrentBlockState(ERROR)
            self.setFormat(0, textLength,
                           PythonHighlighter.Formats["error"])
            return

        for regex, format in PythonHighlighter.Rules:
            i = regex.indexIn(text)
            while i >= 0:
                length = regex.matchedLength()
                self.setFormat(i, length,
                               PythonHighlighter.Formats[format])
                i = regex.indexIn(text, i + length)

        # Slow but good quality highlighting for comments. For more
        # speed, comment this out and add the following to __init__:
        # PythonHighlighter.Rules.append((QRegExp(r"#.*"), "comment"))
        if text.isEmpty():
            pass
        elif text[0] == "#":
            self.setFormat(0, text.length(),
                           PythonHighlighter.Formats["comment"])
        else:
            stack = []
            for i, c in enumerate(text):
                if c in ('"', "'"):
                    if stack and stack[-1] == c:
                        stack.pop()
                    else:
                        stack.append(c)
                elif c == "#" and len(stack) == 0:
                    self.setFormat(i, text.length(),
                                   PythonHighlighter.Formats["comment"])
                    break

        self.setCurrentBlockState(NORMAL)

        if self.stringRe.indexIn(text) != -1:
            return
        # This is fooled by triple quotes inside single quoted strings
        for i, state in ((self.tripleSingleRe.indexIn(text),
                          TRIPLESINGLE),
                         (self.tripleDoubleRe.indexIn(text),
                          TRIPLEDOUBLE)):
            if self.previousBlockState() == state:
                if i == -1:
                    i = text.length()
                    self.setCurrentBlockState(state)
                self.setFormat(0, i + 3,     
                               PythonHighlighter.Formats["string"])
            elif i > -1:
                self.setCurrentBlockState(state)
                self.setFormat(i, text.length(),
                               PythonHighlighter.Formats["string"])


    def rehighlight(self):
        QApplication.setOverrideCursor(QCursor(
                                                    Qt.WaitCursor))
        QSyntaxHighlighter.rehighlight(self)
        QApplication.restoreOverrideCursor()


class TextView(QTextEdit):

    def __init__(self, parent=None):
        super(QTextEdit, self).__init__(parent)
        self.setAcceptRichText(False)
        font = QFont(Config["fontfamily"], Config["fontsize"])
        self.setFont(font)
        self.textcharformat = QTextCharFormat()
        self.textcharformat.setFont(font)


    def currentWord(self, cursor=None):
        if cursor is None:
            cursor = self.textCursor()
        cursor.movePosition(QTextCursor.StartOfWord)
        cursor.movePosition(QTextCursor.EndOfWord,
                            QTextCursor.KeepAnchor)
        return cursor.selectedText()


    def currentLine(self):
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.StartOfLine)
        cursor.movePosition(QTextCursor.EndOfLine,
                            QTextCursor.KeepAnchor)
        return cursor.selectedText()


    def lastNonEmptyLine(self):
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.End)
        cursor.movePosition(QTextCursor.StartOfLine,
                            QTextCursor.KeepAnchor)
        if cursor.selectedText().isEmpty():
            cursor.movePosition(QTextCursor.PreviousCharacter,
                                QTextCursor.KeepAnchor)
            cursor.movePosition(QTextCursor.StartOfLine,
                                QTextCursor.KeepAnchor)
        text = cursor.selectedText()
        if not text.isEmpty():
            while text.endsWith("\n"):
                text.chop(1)
            while text.endsWith(u"\u2029"):
                text.chop(1)
        return text


    def lastLine(self):
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.End)
        cursor.movePosition(QTextCursor.StartOfLine,
                            QTextCursor.KeepAnchor)
        return cursor.selectedText()


class TextEdit(TextView):

    COMPLETION_X_OFFSET = None

    def __init__(self, parent=None):
        super(TextEdit, self).__init__(parent)
        self.setLineWrapMode(QTextEdit.NoWrap)
        self.indent = 0
        self.completionListWidget = None
        self.prefix = ""
        self.classes = set()
        self.defs = set()
        if TextEdit.COMPLETION_X_OFFSET is None:
            TextEdit.COMPLETION_X_OFFSET = QFontMetrics(
                    self.font()).width("x")


    def checkForClassOrDef(self, line):
        match = CLASS_OR_DEF_RE.search(line)
        if match:
            if not match.group(2).startswith("__"):
                if match.group(1) == "class":
                    self.classes.add(match.group(2))
                else:
                    self.defs.add(match.group(2))


    def event(self, event):
        tabwidth = Config["tabwidth"]
        tooltipsize = Config["tooltipsize"]
        indent = " " * tabwidth
        if event.type() == QEvent.KeyPress:
            if event.key() == Qt.Key_Backspace:
                line = self.currentLine()
                if len(line) >= tabwidth and line.endsWith(indent):
                    userCursor = self.textCursor()
                    for _ in range(tabwidth):
                        userCursor.deletePreviousChar()
                    self.indent = max(0, self.indent - 1)
                    return True
            elif event.key() == Qt.Key_Tab:
                if not self.tabChangesFocus():
                    cursor = self.textCursor()
                    cursor.movePosition(
                            QTextCursor.PreviousCharacter,
                            QTextCursor.KeepAnchor)
                    if cursor.selectedText().trimmed().isEmpty():
                        cursor = self.textCursor()
                        cursor.insertText(indent)
                    else:
                        self.complete()
                    return True
                # else leave for base class to handle
            elif event.key() == Qt.Key_ParenLeft:
                cursor = self.textCursor()
                cursor.movePosition(QTextCursor.StartOfLine,
                                    QTextCursor.KeepAnchor)
                name = unicode(cursor.selectedText().section(" ", -1))
                tip = CAT.get(name)
                if tip is not None:
                    rect = self.cursorRect()
                    point = self.mapToGlobal(QPoint(rect.x(),
                                             rect.y()))
                    if len(tip) > tooltipsize:
                        tip = tip[:tooltipsize] + " ..."
                    QToolTip.showText(point, tip)
            elif event.key() in (Qt.Key_Enter,
                                 Qt.Key_Return):
                userCursor = self.textCursor()
                cursor = QTextCursor(userCursor)
                cursor.movePosition(QTextCursor.End)
                insert = "\n"
                cursor = QTextCursor(userCursor)
                cursor.movePosition(QTextCursor.StartOfLine)
                cursor.movePosition(QTextCursor.EndOfLine,
                                    QTextCursor.KeepAnchor)
                line = cursor.selectedText()
                uline = unicode(line)
                checkForCAT(uline)
                self.checkForClassOrDef(uline)
                if line.endsWith(":") or line.endsWith("\\"):
                    for c in line:
                        if c == " ":
                            insert += " "
                        else:
                            break
                    insert += indent
                    self.indent += 1
                elif line.startsWith(indent):
                    for c in line:
                        if c == " ":
                            insert += " "
                        else:
                            break
                userCursor.insertText(insert)
                return True
            elif event.key() in (Qt.Key_Up, Qt.Key_Down,
                            Qt.Key_PageUp, Qt.Key_PageDown):
                cursor = self.textCursor()
                cursor.movePosition(QTextCursor.StartOfLine)
                cursor.movePosition(QTextCursor.EndOfLine,
                                    QTextCursor.KeepAnchor)
                line = cursor.selectedText()
                checkForCAT(unicode(line))
                # Fall through to let the base class handle the movement
        return QTextEdit.event(self, event)


    def complete(self):
        def getWords(prefix):
            return [word for word in list(CAT.keys() + list(WORDS))
                     if len(word) >= MIN_COMPLETION_LEN and
                         word.startswith(prefix)]
                         
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.StartOfLine,
                            QTextCursor.KeepAnchor)
        self.prefix = cursor.selectedText().section(" ", -1)
        if self.prefix.isEmpty():
            return
        pos = self.prefix.length() - 1
        while (self.prefix.at(pos).isLetterOrNumber() or
               self.prefix[pos] == ".") and pos >= 0:
            pos -= 1
        if pos > 0:
            self.prefix = self.prefix.mid(pos + 1)
        if self.prefix.isEmpty():
            return
        words = getWords(self.prefix)
        while not words and self.prefix.contains("."):
            self.prefix = self.prefix.mid(self.prefix.indexIn(".") + 1)
            words = getWords(self.prefix)
        if not words:
            return
        if len(words) > 15:
            length = len(self.prefix)
            words = [word for word in words if "." not in word[length:]]
        firsttime = False
        if self.completionListWidget is None:
            self.completionListWidget = QListWidget(self)
            self.completionListWidget.setWindowFlags(Qt.Popup)
            QShortcut(QKeySequence("Escape"),
                    self.completionListWidget,
                    self.completionListWidget.close)
            self.connect(self.completionListWidget,
                    SIGNAL("itemActivated(QListWidgetItem*)"),
                    self.userCompleted)
            firsttime = True
        self.completionListWidget.clear()
        self.completionListWidget.addItems(sorted(words))
        self.completionListWidget.setCurrentItem(
                self.completionListWidget.item(len(words) // 2))
        self.completionListWidget.scrollTo(
                self.completionListWidget.currentIndex(),
                QListWidget.PositionAtCenter)
                
        rect = self.cursorRect()
        point = self.mapToGlobal(QPoint(rect.x(), rect.y()))
        if not firsttime:
            screenRect = (QApplication.desktop()
                            .availableGeometry(self))
            xDiff = screenRect.width() - (point.x() +
                    self.completionListWidget.width())
            if xDiff < 0:
                point.setX(point.x() + xDiff)
            yDiff = screenRect.height() - (point.y() +
                    self.completionListWidget.height())
            if yDiff < 0:
                point.setY(point.y() + yDiff)
        point.setX(point.x() + TextEdit.COMPLETION_X_OFFSET)
        self.completionListWidget.move(point)
        self.completionListWidget.show()


    def userCompleted(self):
        extra = (self.completionListWidget.currentItem().text()
                 .mid(len(self.prefix)))
        if not extra.isEmpty():
            cursor = self.textCursor()
            cursor.insertText(extra)
        self.completionListWidget.close()


    def gotoLine(self):
        cursor = self.textCursor()
        lino, ok = QInputDialog.getInteger(self,
                            "Sandbox - Goto Line",
                            "Goto line:", cursor.blockNumber() + 1,
                            1, self.document().blockCount())
        if ok:
            cursor.movePosition(QTextCursor.Start)
            cursor.movePosition(QTextCursor.Down,
                    QTextCursor.MoveAnchor, lino - 1)
            self.setTextCursor(cursor)
            self.ensureCursorVisible()


    def gotoMatching(self):
        # move the cursor to the matching ()[]<>{} or do nothing
        OPEN = "([<{"
        CLOSE = ")]>}"
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.PreviousCharacter,
                            QTextCursor.KeepAnchor)
        c = unicode(cursor.selectedText())
        if c not in OPEN + CLOSE:
            cursor = self.textCursor()
            cursor.movePosition(QTextCursor.NextCharacter,
                                QTextCursor.KeepAnchor)
            c = unicode(cursor.selectedText())
            if c in OPEN + CLOSE:
                self.setTextCursor(cursor)
            else:
                return
        i = OPEN.find(c)
        if i > -1:
            movement = QTextCursor.NextCharacter
            stack = 0
            target = CLOSE[i]
        else:
            i = CLOSE.find(c)
            if i == -1:
                return
            movement = QTextCursor.PreviousCharacter
            stack = -1
            target = OPEN[i]
        cursor = self.textCursor()
        while (not (movement == QTextCursor.NextCharacter and
                    cursor.atEnd()) and
               not (movement == QTextCursor.PreviousCharacter and
                    cursor.atStart())):
            cursor.clearSelection()
            cursor.movePosition(movement, QTextCursor.KeepAnchor)
            x = unicode(cursor.selectedText())
            if not x:
                break
            if x == c:
                stack += 1
            elif x == target:
                if stack == 0:
                    cursor.clearSelection()
                    if movement == QTextCursor.PreviousCharacter:
                        cursor.movePosition(
                                QTextCursor.NextCharacter)
                    self.setTextCursor(cursor)
                    break
                else:
                    stack -= 1
    

    def indentRegion(self):
        self._walkTheLines(True, " " * Config["tabwidth"])


    def unindentRegion(self):
        self._walkTheLines(False, " " * Config["tabwidth"])


    def commentRegion(self):
        self._walkTheLines(True, "# ")


    def uncommentRegion(self):
        self._walkTheLines(False, "# ")


    def _walkTheLines(self, insert, text):
        userCursor = self.textCursor()
        userCursor.beginEditBlock()
        start = userCursor.position()
        end = userCursor.anchor()
        if start > end:
            start, end = end, start
        block = self.document().findBlock(start)
        while block.isValid():
            cursor = QTextCursor(block)
            cursor.movePosition(QTextCursor.StartOfBlock)
            if insert:
                cursor.insertText(text)
            else:
                cursor.movePosition(QTextCursor.NextCharacter,
                        QTextCursor.KeepAnchor, len(text))
                if cursor.selectedText() == text:
                    cursor.removeSelectedText()
            block = block.next()
            if block.position() > end:
                break
        userCursor.endEditBlock()


class ShellWidget(QSplitter):
    # Cannot offer a stop command since sending ^C or Del to the
    # interpreter does nothing. Alternative would be to use
    # code.InteractiveInterpreter but I prefer the real thing.

    def __init__(self, parent=None):
        super(ShellWidget, self).__init__(Qt.Vertical, parent)
        self.history = []
        self.historyIndex = -1
        self.output = TextView()
        self.output.setUndoRedoEnabled(False)
        self.output.setReadOnly(True)
        self.output.setTextInteractionFlags(
                Qt.TextSelectableByMouse|
                Qt.TextSelectableByKeyboard)
        self.connect(self.output, SIGNAL("textChanged()"),
                     self.keepOutputVisible)
        self.outputHighlighter = PythonHighlighter(self.output.document())
        self.input = TextEdit()
        self.inputHighlighter = PythonHighlighter(self.input.document())
        self.addWidget(self.output)
        self.addWidget(self.input)
        QWidget.setTabOrder(self.input, self.output)
        self.process = None
        self.restartProcess()
        QShortcut(QKeySequence("F6"), self, self.changeFocus)
        self.setWindowTitle("Sandbox - Shell")


    def restartProcess(self):
        firsttime = False
        if self.process is not None:
            self.endProcess()
            self.output.append("%s RESTARTED %s\n" % ("#" * 20, "#" * 20))
        else:
            firsttime = True
        self.useSeparators = False
        self.starting = True
        self.inTraceback = False
        self.inError = False
        self.process = QProcess(self)
        cwd = Config["cwd"]
        if not cwd.isEmpty() and cwd != ".":
            self.process.setWorkingDirectory(cwd)
        self.process.setProcessChannelMode(QProcess.MergedChannels)
        self.connect(self.process, SIGNAL("readyRead()"),
                     self.readFromPython)
        self.process.start(sys.executable, ["-i"])
        self.process.waitForStarted()
        startup = Config.get("shellstartup")[:]
        if startup is not None:
            for line in startup.split("\n"):
                QTimer.singleShot(0,
                    lambda line=line:
                        self.writeToPython(QString(line + "\n")))
                QTimer.singleShot(0,
                        lambda line=line: checkForCAT(unicode(line)))
        QTimer.singleShot(0, lambda firsttime=firsttime:
                self.setUseSeparators(firsttime=firsttime))


    def setUseSeparators(self, on=True, firsttime=False):
        self.useSeparators = on
        if firsttime and Config["showwindowinfo"]:
            self.output.append("# This is the Python output window.")
            self.output.append("# Enter Python expressions and "
                               "definitions in the input window below, ")
            self.output.append("# then press F5 (or Ctrl+Enter) to "
                               "execute.")
            self.output.append(u"""\
# Use Tab or Ctrl+P for completion (which also works in editor windows),
# and Ctrl+\u2191 and Ctrl+\u2193 for the command history.\n
""")
        self.outputHighlighter.rehighlight()


    def endProcess(self):
        if self.process is not None and self.process.state():
            self.process.write(QByteArray("\x04"))
            self.process.close()
            self.process.terminate()
            QThread.msleep(100)
            if self.process.state():
                self.process.kill()
            self.process = None


    def changeFocus(self):
        if self.input.hasFocus():
            self.output.setFocus()
        else:
            self.input.setFocus()


    def keepOutputVisible(self):
        self.output.moveCursor(QTextCursor.End)
        self.output.ensureCursorVisible()


    def writeSeparator(self, cursor, separator):
        if not self.useSeparators:
            return
        cursor.movePosition(QTextCursor.End)
        while True:
            cursor.movePosition(QTextCursor.PreviousCharacter,
                                QTextCursor.KeepAnchor)
            if cursor.selectedText() == "\n":
                cursor.deleteChar()
            else:
                break
        cursor.insertText("\n%s\n" % separator,
                          self.output.textcharformat)


    def readFromPython(self):
        beforeoutput = Config["beforeoutput"]
        beforeinput = Config["beforeinput"]
        cursor = self.output.textCursor()
        doneSeparator = False
        bytes = QByteArray()
        while self.process.bytesAvailable():
            bytes += self.process.readAll()
        lines = QString.fromUtf8(bytes.data()).split("\n")
        for line in lines:
            if line.endsWith(sys.ps1):
                self.inTraceback = False
                self.inError = False
            line = trimQString(line, sys.ps1)
            line = trimQString(line, sys.ps2)
            if line.isEmpty():
                continue
            if line.startsWith("Traceback"):
                self.inTraceback = True
            if line.startsWith('  File "'):
                self.inError = True
            if self.inError:
                line.replace("<stdin>", "<Shell>").prepend("Error: ")
            if not line.endsWith("\n"):
                line.append("\n")
            if (not doneSeparator and
                not self.starting and
                not self.inTraceback):
                self.writeSeparator(cursor, beforeoutput)
                doneSeparator = True
            cursor = self.output.textCursor()
            cursor.movePosition(QTextCursor.End)
            cursor.insertText(line, self.output.textcharformat)
        if (not self.inTraceback and
            self.output.lastNonEmptyLine() != beforeinput):
            # Gives cleaner output, but it is slow!
            self.output.setPlainText(self.output.toPlainText().replace(
                    "%s\n%s\n" % (beforeinput, beforeoutput), ""))
            self.writeSeparator(cursor, beforeinput)


    def writeToPython(self, text):
        cursor = self.output.textCursor()
        cursor.movePosition(QTextCursor.End)
        cursor.insertText(text, self.output.textcharformat)
        text.append("\n\n")
        self.process.write(text.toUtf8())
        self.process.waitForBytesWritten(-1)
        self.input.clear()


    def execute(self):
        self.starting = False
        text = self.input.toPlainText().trimmed()
        if text.isEmpty():
            text = QString("")
        elif not text.contains("\n"):
            checkForCAT(unicode(text))
        # TODO special case help()
        if text == "license()":
            text.prepend("license.MAXLINES = 9999;")
        else:
            self.history.append(text)
            self.historyIndex = len(self.history)
        text.append("\n")
        self.writeToPython(text)


    def undo(self):
        self.input.undo()


    def redo(self):
        self.input.redo()


    def copy(self):
        if self.input.hasFocus():
            self.input.copy()
        else:
            self.output.copy()


    def cut(self):
        if self.input.hasFocus():
            self.input.cut()
        else:
            self.output.cut()


    def paste(self):
        if self.input.hasFocus():
            self.input.paste()
        else:
            self.output.paste()


    def selectAll(self):
        if self.input.hasFocus():
            self.input.selectAll()
        else:
            self.output.selectAll()


    def complete(self):
        self.input.complete()


    def gotoMatching(self):
        self.input.gotoMatching()
        

    def clearOutput(self):
        self.output.clear()


    def showPrevious(self):
        if -1 < self.historyIndex - 1 < len(self.history):
            self.historyIndex = max(0, self.historyIndex - 1)
            self.input.setText(self.history[self.historyIndex])
            self.input.setFocus()


    def showNext(self):
        if -1 < self.historyIndex + 1 < len(self.history):
            self.historyIndex = min(len(self.history),
                                    self.historyIndex + 1)
            self.input.setText(self.history[self.historyIndex])
        elif self.historyIndex+1 == len(self.history):
            self.historyIndex = len(self.history)
            self.input.clear()
            self.input.setFocus()


class EditWidget(TextEdit):

    def __init__(self, parent=None):
        super(EditWidget, self).__init__(parent)
        self.highlighter = PythonHighlighter(self.document())
        self.findForm = None
        self.process = None
        self.results = None
        self.args = ""
        self.history = [0]
        self.historyIndex = 0
        self.movingInHistory = False
        self.connect(self, SIGNAL("cursorPositionChanged()"),
                     self._updateHistory)


    def _updateHistory(self):
        if not self.movingInHistory:
            lino = self.textCursor().blockNumber()
            if lino != self.history[-1]:
                self.historyIndex = len(self.history)
                self.history.append(lino)


    def gotoPrevious(self):
        self.movingInHistory = True
        self.historyIndex = max(0, self.historyIndex - 1)
        self._gotoHistory()
        self.movingInHistory = False


    def gotoNext(self):
        self.movingInHistory = True
        self.historyIndex = min(len(self.history) - 1,
                                self.historyIndex + 1)
        self._gotoHistory()
        self.movingInHistory = False


    def _gotoHistory(self):
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.Start)
        cursor.movePosition(QTextCursor.Down,
                            QTextCursor.MoveAnchor,
                            self.history[self.historyIndex])
        self.setTextCursor(cursor)
        self.ensureCursorVisible()


    def findText(self):
        if self.findForm is None:
            self.findForm = FindForm(self)
            self.connect(self.findForm, SIGNAL("find"),
                         self.findClicked)
            self.connect(self.findForm, SIGNAL("replace"),
                         self.replaceClicked)
        self.findForm.show()
        self.findForm.activateWindow()
        self.findForm.raise_()


    def findClicked(self, findText, caseSensitive, wholeWords):
        flags = QTextDocument.FindFlags()
        if caseSensitive:
            flags |= QTextDocument.FindCaseSensitively
        if wholeWords:
            flags |= QTextDocument.FindWholeWords
        cursor = self.document().find(findText, self.textCursor(), flags)
        if not cursor.isNull():
            self.setTextCursor(cursor)
        else:
            self.parent().statusBar().showMessage(
                    "'%s' not found" % findText, TIMEOUT)
        return cursor


    def findNext(self):
        if (self.findForm is None or
            self.findForm.findEdit.currentText().isEmpty()):
            self.findText()
        else:
            self.findClicked(self.findForm.findEdit.currentText(),
                    self.findForm.caseSensitiveCheckBox.isChecked(),
                    self.findForm.wholeWordsCheckBox.isChecked())


    def findWordAt(self):
        word = self.currentWord()
        if not word.isEmpty():
            self.findClicked(word, True, True)

 
    def replaceClicked(self, findText, replaceText, caseSensitive,
                       wholeWords):
        cursor = self.findClicked(self.findForm.findEdit.currentText(),
                        self.findForm.caseSensitiveCheckBox.isChecked(),
                        self.findForm.wholeWordsCheckBox.isChecked())
        if cursor.isNull():
            return
        cursor.beginEditBlock()
        start = min(cursor.anchor(), cursor.position())
        cursor.removeSelectedText()
        cursor.insertText(replaceText)
        cursor.setPosition(start)
        cursor.setPosition(start + replaceText.length(),
                           QTextCursor.KeepAnchor)
        cursor.endEditBlock()
        self.setTextCursor(cursor)


    def replaceNext(self):
        if (self.findForm is None or
            self.findForm.findEdit.currentText().isEmpty()):
            self.findText()
        else:
            self.replaceClicked(self.findForm.findEdit.currentText(),
                    self.findForm.replaceEdit.currentText(),
                    self.findForm.caseSensitiveCheckBox.isChecked(),
                    self.findForm.wholeWordsCheckBox.isChecked())


    def setArgs(self):
        args, ok = QInputDialog.getText(self,
                            "Sandbox - Set Arguments",
                            "Command line arguments:",
                            QLineEdit.Normal, self.args)
        self.args = ""
        if ok:
            self.args = unicode(args)


    def execute(self):
        filename = self.parent().filename
        if (self.document().isModified() and
            (QMessageBox.question(self,
                    "Sandbox - Unsaved Changes",
                    "Save unsaved changes in %s before executing?" %
                    filename,
                    QMessageBox.Yes|QMessageBox.No) ==
                    QMessageBox.Yes)):
                self.parent().fileSave()
        if self.results is None:
            self.results = TextView()
            self.results.setUndoRedoEnabled(False)
            self.results.setReadOnly(True)
            self.results.setTextInteractionFlags(
                    Qt.TextSelectableByMouse|
                    Qt.TextSelectableByKeyboard)
            fm = QFontMetrics(self.font())
            # TODO Make the default width & height configurable
            self.results.resize(fm.width("X") * 80, fm.height() * 25)
            self.connect(self.results, SIGNAL("textChanged()"),
                         self.keepResultsVisible)
            QShortcut(QKeySequence("Escape"), self.results,
                            self.results.close)
        else:
            self.results.clear()
        self.results.setWindowTitle("Sandbox - %s %s [Running]" % (
                QFileInfo(filename).fileName(),
                " ".join(self.args.split())))
        self.process = QProcess(self)
        cwd = Config["cwd"]
        if not cwd.isEmpty() and cwd != ".":
            self.process.setWorkingDirectory(cwd)
        self.process.setProcessChannelMode(QProcess.MergedChannels)
        self.connect(self.process, SIGNAL("readyRead()"),
                     self.readResults)
        self.process.start(sys.executable, [filename] + self.args.split())
        self.process.waitForStarted()


    def readResults(self):
        self.results.show()
        self.results.activateWindow()
        self.results.raise_()
        bytes = QByteArray()
        while self.process.bytesAvailable():
            bytes += self.process.readAll()
        self.results.append(QString.fromUtf8(bytes.data()))


    def keepResultsVisible(self):
        self.results.moveCursor(QTextCursor.End)
        self.results.ensureCursorVisible()


    def closeEvent(self, event):
        self.stop()
        event.accept()


    def stop(self):
        if self.process is not None and self.process.state():
            self.process.terminate()
            QThread.msleep(100)
            if self.process.state():
                self.process.kill()
            self.results.setWindowTitle(self.results.windowTitle().replace(
                    "[Running]", "[Stopped]"))


    def raiseResultsWindow(self):
        if self.results is not None:
            self.results.activateWindow()
            self.results.raise_()


class ConfigForm(QDialog):

    def __init__(self, parent=None):
        super(ConfigForm, self).__init__(parent)

        self.highlightingChanged = False
        fm = QFontMetrics(self.font())
        monofont = QFont(Config["fontfamily"], Config["fontsize"])
        pixmap = QPixmap(16, 16)
        self.colors = {}
        self.boldCheckBoxes = {}
        self.italicCheckBoxes = {}
        self.completionCheckBoxes = {}
        self.editors = {}

        generalWidget = QWidget()
        self.rememberGeometryCheckBox = QCheckBox(
                "&Remember Geometry")
        self.rememberGeometryCheckBox.setToolTip("<p>Check this to make "
                "Sandbox remember the size and position of the Shell "
                "window and one Editor window")
        self.rememberGeometryCheckBox.setChecked(
                Config["remembergeometry"])
        self.editorWindowRadioButton = QRadioButton(
                "Start With Editor &Window")
        self.shellWindowRadioButton = QRadioButton(
                "Start With &Shell Window")
        startWithButtonGroup = QButtonGroup(self)
        startWithButtonGroup.setExclusive(True)
        startWithButtonGroup.addButton(self.editorWindowRadioButton)
        startWithButtonGroup.addButton(self.shellWindowRadioButton)
        startwithshell = Config["startwithshell"]
        self.shellWindowRadioButton.setChecked(startwithshell)
        self.editorWindowRadioButton.setChecked(not startwithshell)
        self.autoHideFindDlgCheckBox = QCheckBox(
                "Automati&cally Hide the Find and Replace dialog")
        self.autoHideFindDlgCheckBox.setToolTip("<p>If checked, when you "
                "press Find or Replace the dialog will be hidden; "
                "further finds and replaces can be done through the Edit "
                "menu (which lists the keyboard shortcuts). Uncheck this "
                "if you prefer the dialog to stay visible and to click "
                "its buttons")
        self.autoHideFindDlgCheckBox.setChecked(
                Config["autohidefinddialog"])
        self.backupLineEdit = QLineEdit(Config["backupsuffix"])
        self.backupLineEdit.setToolTip("<p>If nonempty, a backup will be "
                "kept with the given suffix. If empty, no backup will be "
                "made.")
        regex = QRegExp(r"[~.].*")
        self.backupLineEdit.setValidator(QRegExpValidator(regex,
                                                                 self))
        self.backupLineEdit.setFont(monofont)
        backupLabel = QLabel("&Backup suffix:")
        backupLabel.setBuddy(self.backupLineEdit)
        regex = QRegExp(r"#.*")
        self.inputLineEdit = QLineEdit(Config["beforeinput"])
        self.inputLineEdit.setValidator(QRegExpValidator(regex,
                                                                self))
        self.inputLineEdit.setInputMask("\#" + "x" * 40)
        self.inputLineEdit.setFont(monofont)
        inputPromptLabel = QLabel("&Input Prompt:")
        inputPromptLabel.setBuddy(self.inputLineEdit)
        self.outputLineEdit = QLineEdit(Config["beforeoutput"])
        self.outputLineEdit.setValidator(QRegExpValidator(regex,
                                                                 self))
        self.outputLineEdit.setInputMask("\#" + "x" * 40)
        self.outputLineEdit.setFont(monofont)
        outputPromptLabel = QLabel("&Output Prompt:")
        outputPromptLabel.setBuddy(self.outputLineEdit)
        self.cwdLineEdit = QLineEdit(Config["cwd"])
        cwdLabel = QLabel("Working &Directory:")
        cwdLabel.setBuddy(self.cwdLineEdit)
        self.showWindowInfoCheckBox = QCheckBox(
                "Show Window Information at Start&up")
        self.showWindowInfoCheckBox.setToolTip("<p>Uncheck this to stop "
                "the `This window shows Python's output' messages")
        self.showWindowInfoCheckBox.setChecked(Config["showwindowinfo"])
        self.toolTipSizeSpinBox = QSpinBox()
        self.toolTipSizeSpinBox.setAlignment(Qt.AlignVCenter|
                                             Qt.AlignRight)
        self.toolTipSizeSpinBox.setRange(20, MAX_TOOLTIP_LEN)
        self.toolTipSizeSpinBox.setSuffix(" chars")
        self.toolTipSizeSpinBox.setValue(Config["tooltipsize"])
        tooltipSizeLabel = QLabel("Max. Tooltip &Length:")
        tooltipSizeLabel.setBuddy(self.toolTipSizeSpinBox)
        self.maxLinesSizeSpinBox = QSpinBox()
        self.maxLinesSizeSpinBox.setAlignment(Qt.AlignVCenter|
                                              Qt.AlignRight)
        self.maxLinesSizeSpinBox.setRange(0, 10000)
        self.maxLinesSizeSpinBox.setSuffix(" lines")
        self.maxLinesSizeSpinBox.setValue(Config["maxlinestoscan"])
        self.maxLinesSizeSpinBox.setToolTip("<p>The maximum lines to "
                "scan for function, method, and class names, and for "
                "imports when a file is loaded. This is used for "
                "setting up completions and tooltips and for the Goto "
                "class and Goto def submenus. It can be slow for large "
                "files.")
        maxLinesSizeLabel = QLabel("&Max. Lines to Scan:")
        maxLinesSizeLabel.setBuddy(self.maxLinesSizeSpinBox)
        self.docPathLineEdit = QLineEdit(Config["pythondocpath"])
        self.docPathLineEdit.setToolTip('<p>Enter your preferred location '
                '(web address or path on local hard drive) of Python '
                'documentation to be shown when selecting "Python '
                'Documentation" from the Help menu.')
        docPathButton = QPushButton("...")
        docPathButton.setToolTip("Open file dialog to choose path")
        self.connect(docPathButton, SIGNAL("clicked()"),
                     self.setDocPath)
        docPathLabel = QLabel("P&ython Documentation:")
        docPathLabel.setBuddy(self.docPathLineEdit)
        minWidth = 0
        for label in (backupLabel, inputPromptLabel, outputPromptLabel,
                cwdLabel, tooltipSizeLabel, maxLinesSizeLabel,
                docPathLabel):
            minWidth = max(minWidth, fm.width(label.text()))
        for label in (backupLabel, inputPromptLabel, outputPromptLabel,
                cwdLabel, tooltipSizeLabel, maxLinesSizeLabel,
                docPathLabel):
            label.setMinimumWidth(minWidth)
        vbox = QVBoxLayout()
        vbox.addWidget(self.rememberGeometryCheckBox)
        hbox = QHBoxLayout()
        hbox.addWidget(self.editorWindowRadioButton)
        hbox.addWidget(self.shellWindowRadioButton)
        hbox.addStretch()
        vbox.addLayout(hbox)
        vbox.addWidget(self.autoHideFindDlgCheckBox)
        hbox = QHBoxLayout()
        hbox.addWidget(backupLabel)
        hbox.addWidget(self.backupLineEdit)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(inputPromptLabel)
        hbox.addWidget(self.inputLineEdit)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(outputPromptLabel)
        hbox.addWidget(self.outputLineEdit)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(cwdLabel)
        hbox.addWidget(self.cwdLineEdit)
        vbox.addLayout(hbox)
        vbox.addWidget(self.showWindowInfoCheckBox)
        hbox = QHBoxLayout()
        hbox.addWidget(tooltipSizeLabel)
        hbox.addWidget(self.toolTipSizeSpinBox)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(maxLinesSizeLabel)
        hbox.addWidget(self.maxLinesSizeSpinBox)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(docPathLabel)
        hbox.addWidget(self.docPathLineEdit)
        hbox.addWidget(docPathButton)
        vbox.addLayout(hbox)
        vbox.addStretch()
        generalWidget.setLayout(vbox)

        highlightingWidget = QWidget()
        self.tabWidthSpinBox = QSpinBox()
        self.tabWidthSpinBox.setAlignment(Qt.AlignVCenter|
                                          Qt.AlignRight)
        self.tabWidthSpinBox.setRange(2, 20)
        self.tabWidthSpinBox.setSuffix(" spaces")
        self.tabWidthSpinBox.setValue(Config["tabwidth"])
        tabWidthLabel = QLabel("&Tab width:")
        tabWidthLabel.setBuddy(self.tabWidthSpinBox)
        self.fontComboBox = QFontComboBox()
        self.fontComboBox.setCurrentFont(monofont)
        fontLabel = QLabel("&Font:")
        fontLabel.setBuddy(self.fontComboBox)
        self.fontSpinBox = QSpinBox()
        self.fontSpinBox.setAlignment(Qt.AlignVCenter|
                                      Qt.AlignRight)
        self.fontSpinBox.setRange(6, 20)
        self.fontSpinBox.setSuffix(" pt")
        self.fontSpinBox.setValue(Config["fontsize"])

        vbox = QVBoxLayout()
        hbox = QHBoxLayout()
        hbox.addWidget(tabWidthLabel)
        hbox.addWidget(self.tabWidthSpinBox)
        hbox.addStretch()
        vbox.addLayout(hbox)
        hbox = QHBoxLayout()
        hbox.addWidget(fontLabel)
        hbox.addWidget(self.fontComboBox)
        hbox.addWidget(self.fontSpinBox)
        hbox.addStretch()
        vbox.addLayout(hbox)

        minWidth = 0
        minButtonWidth = 0
        count = 1
        labels = []
        buttons = []
        for name, labelText in (("normal", "Normal:"),
                ("keyword", "Keywords:"), ("builtin", "Builtins:"),
                ("constant", "Constants:"), ("decorator", "Decorators:"),
                ("comment", "Comments:"), ("string", "Strings:"),
                ("number", "Numbers:"), ("error", "Errors:"),
                ("pyqt", "PyQt:")):
            label = QLabel(labelText)
            minWidth = max(minWidth, fm.width(label.text()))
            labels.append(label)
            boldCheckBox = QCheckBox("Bold")
            boldCheckBox.setChecked(Config["%sfontbold" % name])
            self.boldCheckBoxes[name] = boldCheckBox
            italicCheckBox = QCheckBox("Italic")
            italicCheckBox.setChecked(Config["%sfontitalic" % name])
            self.italicCheckBoxes[name] = italicCheckBox
            self.colors[name] = [Config["%sfontcolor" % name], None]
            pixmap.fill(QColor(self.colors[name][0]))
            if count <= 9:
                colorButton = QPushButton("&%d Color..." % count)
                count += 1
            elif name == "pyqt":
                colorButton = QPushButton("&Q Color...")
            else:
                colorButton = QPushButton("Color...")
            minButtonWidth = max(minButtonWidth,
                    10 + pixmap.width() + fm.width(colorButton.text()))
            buttons.append(colorButton)
            colorButton.setIcon(QIcon(pixmap))
            self.colors[name][1] = colorButton
            hbox = QHBoxLayout()
            hbox.addWidget(label)
            hbox.addWidget(boldCheckBox)
            hbox.addWidget(italicCheckBox)
            hbox.addWidget(colorButton)
            hbox.addStretch()
            vbox.addLayout(hbox)
            self.connect(colorButton, SIGNAL("clicked()"),
                        lambda name=name: self.setColor(name))
        for label in labels:
            label.setMinimumWidth(minWidth)
        for button in buttons:
            button.setMinimumWidth(minButtonWidth)
        vbox.addStretch()
        highlightingWidget.setLayout(vbox)

        tabWidget = QTabWidget()
        tabWidget.addTab(generalWidget, "&General")
        tabWidget.addTab(highlightingWidget, "&Highlighting")

        for name, label, msg in (
                ("newfile", "On &New File",
                 "<font color=green><i>The text here is automatically "
                 "inserted into new files.<br>It may be convenient to add "
                 "your standard imports and copyright notice here."),
                ("shellstartup", "&At Startup",
                 "<font color=green><i>Sandbox executes the lines above "
                 "whenever the Python interpreter is started.<br>"
                 "Use them to add convenience, e.g. "
                 "</i><b>from math import *; import re;</b> "
                 "<font color=green><i>etc.<br>"
                 "Changes made here only take "
                 "effect when Sandbox is next run."
                 "<hr><font color=red>The codecs and sys imports, "
                 "and the other codecs lines should<br>not be changed "
                 "unless you are an expert.</font>")):
            editor = TextEdit()
            editor.setPlainText(Config[name])
            editor.setTabChangesFocus(True)
            PythonHighlighter(editor.document())
            vbox = QVBoxLayout()
            vbox.addWidget(editor, 1)
            vbox.addWidget(QLabel(msg))
            widget = QWidget()
            widget.setLayout(vbox)
            tabWidget.addTab(widget, label)
            self.editors[name] = editor

        buttonBox = QDialogButtonBox(QDialogButtonBox.Ok|
                                           QDialogButtonBox.Cancel)
        layout = QVBoxLayout()
        layout.addWidget(tabWidget)
        layout.addWidget(buttonBox)
        self.setLayout(layout)

        self.connect(buttonBox, SIGNAL("accepted()"), self.accept)
        self.connect(buttonBox, SIGNAL("rejected()"), self.reject)

        self.setWindowTitle("Sandbox - Configure")


    def updateUi(self):
        pass # TODO validation, e.g., valid shellstartup, etc.


    def setDocPath(self):
        path = QFileDialog.getOpenFileName(self,
                    "Sandbox - Open File", self.docPathLineEdit.text())
        if not path.isEmpty():
            self.docPathLineEdit.setText(path)


    def setColor(self, which):
        color = QColorDialog.getColor(
                        QColor(self.colors[which][0]), self)
        if color is not None:
            self.colors[which][0] = color.name()
            pixmap = QPixmap(16, 16)
            pixmap.fill(QColor(color.name()))
            self.colors[which][1].setIcon(QIcon(pixmap))


    def accept(self):
        Config["remembergeometry"] = (self.rememberGeometryCheckBox
                                      .isChecked())
        Config["showwindowinfo"] = self.showWindowInfoCheckBox.isChecked()
        Config["startwithshell"] = self.shellWindowRadioButton.isChecked()
        Config["autohidefinddialog"] = (self.autoHideFindDlgCheckBox
                                        .isChecked())
        Config["backupsuffix"] = self.backupLineEdit.text()
        Config["beforeinput"] = self.inputLineEdit.text()
        Config["beforeoutput"] = self.outputLineEdit.text()
        Config["cwd"] = self.cwdLineEdit.text()
        for name in ("shellstartup", "newfile"):
            Config[name] = unicode(self.editors[name].toPlainText())
        Config["tabwidth"] = self.tabWidthSpinBox.value()
        Config["tooltipsize"] = self.toolTipSizeSpinBox.value()
        Config["maxlinestoscan"] = self.maxLinesSizeSpinBox.value()
        Config["pythondocpath"] = self.docPathLineEdit.text()
        family = self.fontComboBox.currentFont().family()
        if Config["fontfamily"] != family:
            self.highlightingChanged = True
            Config["fontfamily"] = family
        size = self.fontSpinBox.value()
        if Config["fontsize"] != size:
            self.highlightingChanged = True
            Config["fontsize"] = size
        for name in ("normal", "keyword", "builtin", "constant",
                "decorator", "comment", "string", "number", "error",
                "pyqt"):
            bold = self.boldCheckBoxes[name].isChecked()
            if Config["%sfontbold" % name] != bold:
                self.highlightingChanged = True
                Config["%sfontbold" % name] = bold
            italic = self.italicCheckBoxes[name].isChecked()
            if Config["%sfontitalic" % name] != italic:
                self.highlightingChanged = True
                Config["%sfontitalic" % name] = italic
            color = self.colors[name][0]
            if Config["%sfontcolor" % name] != color:
                self.highlightingChanged = True
                Config["%sfontcolor" % name] = color
        QDialog.accept(self)


class MainWindow(QMainWindow):

    NextId = 1
    Instances = set()
    Shell = None
    Toolbars = {}

    def __init__(self, filename=QString(), isShell=False,
                 parent=None):
        super(MainWindow, self).__init__(parent)
        self.setAttribute(Qt.WA_DeleteOnClose)
        MainWindow.Instances.add(self)
        self.setWindowTitle("Sandbox[*]")
        if isShell:
            self.editor = ShellWidget()
            MainWindow.Shell = self
        else:
            self.editor = EditWidget()
        self.setCentralWidget(self.editor)

        fileNewAction = self.createAction("&New File", self.fileNew,
                QKeySequence.New, "filenew", "Create a Python file")
        if not isShell:
            fileNewShellAction = self.createAction("Sh&ell",
                    self.fileNewShell, icon="filenew",
                    tip="Create a new (or go to the existing) Shell")
        fileOpenAction = self.createAction("&Open...", self.fileOpen,
                QKeySequence.Open, "fileopen",
                "Open an existing Python file")
# TODO
#        fileOpenRecentAction = self.createAction("&Open Recent",
#                self.fileOpenRecent, icon="fileopen",
#                tip="Open an existing Python file")
        if not isShell:
            fileOpenAtAction = self.createAction(
                    "Open &File at Cursor", self.fileOpenAt,
                    "Ctrl+Shift+O", "fileopen",
                    "Open the file whose name is at the cursor position")
            fileSaveAction = self.createAction("&Save", self.fileSave,
                    QKeySequence.Save, "filesave", "Save the file")
            fileSaveAsAction = self.createAction("Save &As...",
                    self.fileSaveAs, icon="filesaveas",
                    tip="Save the file using a new filename")
        fileSaveAllAction = self.createAction("Save A&ll",
                self.fileSaveAll, icon="filesaveall",
                tip="Save all the files")
        fileConfigureAction = self.createAction("Config&ure...",
                self.fileConfigure, icon="fileconfigure",
                tip="Configure Sandbox")
        fileCloseAction = self.createAction("&Close", self.close,
                QKeySequence.Close, "fileclose",
                "Close this Python editor")
        fileQuitAction = self.createAction("&Quit", self.fileQuit,
                "Ctrl+Q", "filequit", "Close the application")
        editUndoAction = self.createAction("&Undo", self.editor.undo,
                QKeySequence.Undo, "editundo",
                "Undo the last editing action")
        editRedoAction = self.createAction("&Redo", self.editor.redo,
                QKeySequence.Redo, "editredo",
                "Redo the last editing action")
        editCopyAction = self.createAction("&Copy", self.editor.copy,
                QKeySequence.Copy, "editcopy",
                "Copy text to the clipboard")
        editCutAction = self.createAction("Cu&t", self.editor.cut,
                QKeySequence.Cut, "editcut",
                "Cut text to the clipboard")
        editPasteAction = self.createAction("&Paste",
                self.editor.paste, QKeySequence.Paste, "editpaste",
                "Paste in the clipboard's text")
        editSelectAllAction = self.createAction("Select &All",
                self.editor.selectAll, QKeySequence.SelectAll,
                "editselectall", "Select all the editor's text")
        editCompleteAction = self.createAction("Com&plete",
                self.editor.complete, "Ctrl+P", "editcomplete",
                "Complete the word (can also use Tab)")
        if isShell:
            editClearOutputAction = self.createAction("Clear &Output",
                    self.editor.clearOutput, icon="editclear",
                    tip="Clear the output text")
        else:
            editFindAction = self.createAction("&Find...",
                    self.editor.findText, QKeySequence.Find,
                    "editfind", "Find the given text")
            editFindNextAction = self.createAction("Find &Next",
                    self.editor.findNext, QKeySequence.FindNext,
                    "editfindnext",
                    "Find the next occurrence of the given text")
            editFindWordAtAction = self.createAction(
                    "Find &Word at Cursor", self.editor.findWordAt,
                    "Shift+F3", "editfindnext",
                    "Find the next occurrence of the word at the cursor")
            editReplaceNextAction = self.createAction("R&eplace Next",
                    self.editor.replaceNext, QKeySequence.Replace,
                    "editreplace",
                    "Replace the next occurrence of the given text")
            editIndentRegionAction = self.createAction("&Indent Region",
                    self.editor.indentRegion, "Ctrl+]", "editindent",
                    "Indent the selected text or the current line")
            editUnindentRegionAction = self.createAction(
                    "Unin&dent Region", self.editor.unindentRegion,
                    "Ctrl+[", "editunindent",
                    "Unindent the selected text or the current line")
            editCommentRegionAction = self.createAction("C&omment Region",
                    self.editor.commentRegion, icon="editcomment",
                    tip=("Comment out the selected text or the "
                         "current line"))
            editUncommentRegionAction = self.createAction(
                    "Uncomment Re&gion", self.editor.uncommentRegion,
                    icon="edituncomment",
                    tip="Uncomment the selected text or the current line")
        actionRunAction = self.createAction("E&xecute",
                self.editor.execute, None, "actionrun",
                "Execute the input window's code or run the current file")
        actionRunAction.setShortcuts([QKeySequence("F5"),
                QKeySequence("Ctrl+Enter"),
                QKeySequence("Ctrl+Return")])
        if not isShell:
            actionSetArgsAction = self.createAction("Set &arguments...",
                    self.editor.setArgs, icon="actionsetargs",
                    tip="Set the command line arguments")
            actionStopAction = self.createAction("&Stop",
                    self.editor.stop, icon="actionstop",
                    tip="Forcibly stop the application")
        else:
            actionRestartAction = self.createAction("Restart &Python",
                    self.editor.restartProcess, icon="actionrestart",
                    tip="Stop the interpreter and start a new one")
            actionShowPrevAction = self.createAction(
                    "Show Previous Command", self.editor.showPrevious,
                    "Ctrl+Up", "previous",
                    ("Show the previous command ready for editing "
                     "and running"))
            actionShowNextAction = self.createAction(
                    "Show Next Command", self.editor.showNext,
                    "Ctrl+Down", "next",
                    ("Show the next command ready for editing "
                     "and running"))
        helpHelpAction = self.createAction("&Help", self.helpHelp,
                QKeySequence.HelpContents, icon="helphelp",
                tip="Online help")
        helpPydocAction = self.createAction("&Python Documentation",
                self.helpPydoc, "Ctrl+H", "docs", 
                tip="Open Python Documentation in a Web Browser")
        helpAboutAction = self.createAction("&About", self.helpAbout,
                icon="icon", tip="About Sandbox")

        fileMenu = self.menuBar().addMenu("&File")
        self.addActions(fileMenu, (fileNewAction,))
        if not isShell:
            self.addActions(fileMenu, (fileNewShellAction,))
        self.addActions(fileMenu, (fileOpenAction,
            # fileOpenRecentAction # TODO
            ))
        if not isShell:
            self.addActions(fileMenu, (fileOpenAtAction, fileSaveAction,
                                       fileSaveAsAction))
        self.addActions(fileMenu, (fileSaveAllAction, None,
                fileConfigureAction, None, fileCloseAction,
                fileQuitAction))
        editMenu = self.menuBar().addMenu("&Edit")
        self.addActions(editMenu, (editUndoAction, editRedoAction, None,
                editCopyAction, editCutAction, editPasteAction,
                editSelectAllAction, None, editCompleteAction))
        if isShell:
            self.addActions(editMenu, (None, editClearOutputAction,))
        else:
            self.addActions(editMenu, (None, editFindAction,
                editFindNextAction, editFindWordAtAction,
                editReplaceNextAction, None, editIndentRegionAction,
                editUnindentRegionAction, editCommentRegionAction,
                editUncommentRegionAction))
        self.gotoMenu = self.menuBar().addMenu("&Goto")
        self.connect(self.gotoMenu, SIGNAL("aboutToShow()"),
                     self.updateGotoMenu)
        actionMenu = self.menuBar().addMenu("&Action")
        self.addActions(actionMenu, (actionRunAction,))
        if not isShell:
            self.addActions(actionMenu, (actionSetArgsAction,
                    actionStopAction))
        else:
            self.addActions(actionMenu, (actionRestartAction, None,
                    actionShowPrevAction, actionShowNextAction))
        viewMenu = self.menuBar().addMenu("&View")
        self.windowMenu = self.menuBar().addMenu("&Window")
        self.connect(self.windowMenu, SIGNAL("aboutToShow()"),
                     self.updateWindowMenu)
        helpMenu = self.menuBar().addMenu("&Help")
        self.addActions(helpMenu, (helpHelpAction, helpPydocAction,
                                   helpAboutAction))

        self.fileToolbar = self.addToolBar("File Toolbar")
        self.fileToolbar.setObjectName("FileToolbar")
        MainWindow.Toolbars[self.fileToolbar] = None
        self.addActions(self.fileToolbar, (fileNewAction, fileOpenAction))
        if not isShell:
            self.addActions(self.fileToolbar, (fileSaveAction,))
        self.editToolbar = self.addToolBar("Edit Toolbar")
        self.editToolbar.setObjectName("EditToolbar")
        MainWindow.Toolbars[self.editToolbar] = None
        self.addActions(self.editToolbar, (editUndoAction, editRedoAction,
                None, editCopyAction, editCutAction, editPasteAction))
        if not isShell:
            self.addActions(self.editToolbar, (None, editFindAction,
                    editFindNextAction, editReplaceNextAction, None,
                    editIndentRegionAction, editUnindentRegionAction,
                    editCommentRegionAction, editUncommentRegionAction))
        self.actionToolbar = self.addToolBar("Action Toolbar")
        self.actionToolbar.setObjectName("ActionToolbar")
        MainWindow.Toolbars[self.actionToolbar] = None
        self.addActions(self.actionToolbar, (actionRunAction,))
        if not isShell:
            self.addActions(self.actionToolbar, (actionStopAction,))
        else:
            self.addActions(self.actionToolbar, (actionRestartAction, None,
                    actionShowPrevAction, actionShowNextAction))
        for toolbar in (self.fileToolbar, self.editToolbar,
                        self.actionToolbar):
            action = viewMenu.addAction("&%s" % toolbar.windowTitle())
            self.connect(action, SIGNAL("toggled(bool)"),
                         self.toggleToolbars)
            action.setCheckable(True)
            MainWindow.Toolbars[toolbar] = action

        self.connect(self, SIGNAL("destroyed(QObject*)"),
                     MainWindow.updateInstances)

        if not isShell:
            status = self.statusBar()
            status.setSizeGripEnabled(False)
            status.showMessage("Ready", 5000)
            self.columnCountLabel = QLabel("(empty)")
            status.addPermanentWidget(self.columnCountLabel)
            self.lineCountLabel = QLabel("(empty)")
            status.addPermanentWidget(self.lineCountLabel)
            self.connect(self.editor,
                         SIGNAL("cursorPositionChanged()"),
                         self.updateIndicators)
            self.connect(self.editor.document(),
                         SIGNAL("blockCountChanged(int)"),
                         self.updateIndicators)

        if Config["remembergeometry"]:
            if isShell:
                self.resize(Config["shellwidth"], Config["shellheight"])
                self.move(Config["shellx"], Config["shelly"])
            else:
                self.resize(Config["windowwidth"],
                            Config["windowheight"])
                if int(isShell) + len(MainWindow.Instances) <= 2:
                    self.move(Config["windowx"], Config["windowy"])

        self.restoreState(Config["toolbars"])
        self.filename = QString(".")
        if isShell:
            self.editor.restoreState(Config["splitter"])
            self.setWindowTitle("Sandbox - Shell")
        else:
            self.filename = filename
            if self.filename.isEmpty():
                self.filename = QString("unnamed%d.py" %
                                               MainWindow.NextId)
                MainWindow.NextId += 1
                self.editor.setText(Config["newfile"])
                self.editor.moveCursor(QTextCursor.End)
                self.editor.document().setModified(False)
                self.setWindowModified(False)
                self.setWindowTitle("Sandbox - %s[*]" % self.filename)
            else:
                self.loadFile()
            self.connect(self.editor, SIGNAL("textChanged()"),
                         self.updateDirty)
        self.updateGotoMenu()
        QTimer.singleShot(0, self.updateToolbars)


    @staticmethod
    def updateInstances(qobj):
        MainWindow.Instances = set([window for window
                in MainWindow.Instances if isAlive(window)])
        if MainWindow.Shell is not None and not isAlive(MainWindow.Shell):
            MainWindow.Shell = None


    def createAction(self, text, slot=None, shortcut=None, icon=None,
                     tip=None, checkable=False, signal="triggered()"):
        action = QAction(text, self)
        if icon is not None:
            action.setIcon(getIcon("%s.png" % icon))
        if shortcut is not None:
            action.setShortcut(shortcut)
        if tip is not None:
            action.setToolTip(tip)
            action.setStatusTip(tip)
        if slot is not None:
            self.connect(action, SIGNAL(signal), slot)
        if checkable:
            action.setCheckable(True)
        return action


    def addActions(self, target, actions):
        for action in actions:
            if action is None:
                target.addSeparator()
            else:
                target.addAction(action)


    def updateDirty(self):
        self.setWindowModified(self.editor.document().isModified())


    def updateIndicators(self):
        lines = self.editor.document().blockCount()
        cursor = self.editor.textCursor()
        self.columnCountLabel.setText("Column %d" % (
                cursor.columnNumber() + 1))
        if lines == 0:
            text = "(empty)"
        else:
            text = "Line %d of %d" % (cursor.blockNumber() + 1, lines)
        self.lineCountLabel.setText(text)


    def updateToolbars(self):
        for toolbar, action in MainWindow.Toolbars.items():
            action.setChecked(toolbar.isVisible())


    def toggleToolbars(self, on):
        title = self.sender().text()
        for toolbar, action in MainWindow.Toolbars.items():
            if action.text() == title:
                toolbar.setVisible(on)
                action.setChecked(on)


    def closeEvent(self, event):
        if self == MainWindow.Shell:
            self.editor.endProcess()
            if Config["remembergeometry"]:
                Config["shellwidth"] = self.width()
                Config["shellheight"] = self.height()
                Config["shellx"] = self.x()
                Config["shelly"] = self.y()
            Config["splitter"] = self.editor.saveState()
        else:
            if self.editor.document().isModified():
                reply = QMessageBox.question(self,
                        "Sandbox - Unsaved Changes",
                        "Save unsaved changes in %s" % self.filename,
                        QMessageBox.Save|QMessageBox.Discard|
                        QMessageBox.Cancel)
                if reply == QMessageBox.Save:
                    self.fileSave()
                elif reply == QMessageBox.Cancel:
                    event.ignore()
                    return
                # else accept and discard
            if Config["remembergeometry"]:
                Config["windowwidth"] = self.width()
                Config["windowheight"] = self.height()
                Config["windowx"] = self.x()
                Config["windowy"] = self.y()
            if self.editor.findForm is not None:
                Config["findcasesensitive"] = (self.editor.findForm 
                        .caseSensitiveCheckBox.isChecked())
                Config["findwholewords"] = (self.editor.findForm
                        .wholeWordsCheckBox.isChecked())
        Config["toolbars"] = self.saveState()
        del MainWindow.Toolbars[self.fileToolbar]
        del MainWindow.Toolbars[self.editToolbar]
        del MainWindow.Toolbars[self.actionToolbar]
        event.accept()


    def fileConfigure(self):
        form = ConfigForm(self)
        if form.exec_():
            # Should only do this if the highlighting was actually
            # changed since it is computationally expensive.
            if form.highlightingChanged:
                font = QFont(Config["fontfamily"],
                                   Config["fontsize"])
                textcharformat = QTextCharFormat()
                textcharformat.setFont(font)
                PythonHighlighter.initializeFormats()
                for window in MainWindow.Instances:
                    if isAlive(window):
                        if window == MainWindow.Shell:
                            window.editor.input.setFont(font)
                            window.editor.input.textcharformat = (
                                    textcharformat)
                            window.editor.inputHighlighter.rehighlight()
                            window.editor.output.setFont(font)
                            window.editor.output.textcharformat = (
                                    textcharformat)
                            window.editor.outputHighlighter.rehighlight()
                        else:
                            window.statusBar().showMessage(
                                    "Rehighlighting...")
                            window.editor.setFont(font)
                            window.editor.textcharformat = textcharformat
                            window.editor.highlighter.rehighlight()
                            window.statusBar().clearMessage()
            saveConfig()


    def fileQuit(self):
        QApplication.closeAllWindows()
        shell = MainWindow.Shell
        if shell is not None:
            shell.editor.endProcess()


    def fileNew(self):
        MainWindow().show()


    def fileNewShell(self):
        if MainWindow.Shell is not None and isAlive(MainWindow.Shell):
            MainWindow.Shell.activateWindow()
            MainWindow.Shell.raise_()
        else:
            MainWindow(isShell=True).show()


    def fileOpen(self):
        if not self.filename.isEmpty():
            path = QFileInfo(self.filename).path()
        else:
            path = "."
        filename = QFileDialog.getOpenFileName(self,
                        "Sandbox - Open File", path,
                        "Python files (*.py *.pyw)\nAny file (*)")
        if not filename.isEmpty():
            # To prevent opening the same file twice
            for window in MainWindow.Instances:
                if isAlive(window) and window != MainWindow.Shell:
                    if window.filename == filename:
                        window.activateWindow()
                        window.raise_()
                        return
            if (MainWindow.Shell != self and
                not self.editor.document().isModified() and
                self.filename.startsWith("unnamed")):
                self.filename = filename
                self.loadFile()
            else:
                MainWindow(filename).show()


    def loadFile(self):
        # File loading is slow due to reading CAT data and highlighting,
        # but mostly due to the former. If you load one PyQt4 app, it
        # will be slow, but subsequent ones will be quick becaue all the
        # CAT data will have been gathered already.
        QApplication.setOverrideCursor(QCursor(
                                                    Qt.WaitCursor))
        fh = None
        try:
            try:
                fh = QFile(self.filename)
                if not fh.open(QIODevice.ReadOnly):
                    raise IOError, unicode(fh.errorString())
                stream = QTextStream(fh)
                stream.setCodec("UTF-8")
                text = stream.readAll()
                self.editor.setPlainText(text)
                self.editor.document().setModified(False)
                # Get function, method, and class names for completion;
                # get imports for CAT.
                for i, line in enumerate(text.split("\n")): # This is slow!
                    if i >= Config["maxlinestoscan"]:
                        break
                    if CATABLE_LINE_RE.indexIn(line) > -1:
                        uline = unicode(line)
                        checkForCAT(uline)
                        self.editor.checkForClassOrDef(uline)
            except (IOError, OSError), e:
                QMessageBox.warning(self, "Sandbox - Load Error",
                        "Failed to load %s: %s" % (self.filename, e))
        finally:
            if fh is not None:
                fh.close()
            QApplication.restoreOverrideCursor()
        self.editor.document().setModified(False)
        self.setWindowModified(False)
        self.setWindowTitle("Sandbox - %s[*]" %
                            QFileInfo(self.filename).fileName())


    def fileOpenRecent(self):
        print "fileOpenRecent" # TODO 


    def fileOpenAt(self):
        filename = self.editor.currentWord()
        if filename in ("py", "pyw"):
            cursor = self.editor.textCursor()
            cursor.movePosition(QTextCursor.PreviousWord)
            filename = self.editor.currentWord(cursor) + "." + filename
        if filename.isEmpty():
            return
        filename = unicode(filename)
        dir = os.path.dirname(unicode(QDir(
                                            self.filename).absolutePath()))
        candidates = [filename, os.path.join(dir, filename)]
        if not filename.endswith((".py", ".pyw")):
            filename += ".py"
            candidates.append(filename)
            candidates.append(os.path.join(dir, filename))
        for path in sys.path:
            candidates.append(os.path.join(path, filename))
        for candidate in candidates:
            if QFile.exists(candidate):
                QApplication.setOverrideCursor(QCursor(
                                                    Qt.WaitCursor))
                MainWindow(QString(candidate)).show()
                QApplication.restoreOverrideCursor()
                break
        else:
            self.statusBar().showMessage("'%s' not found" % filename,
                                         TIMEOUT)


    def fileSave(self):
        if self.filename.startsWith("unnamed"):
            return self.fileSaveAs()
        if (not Config["backupsuffix"].isEmpty() and
            QFile.exists(self.filename)):
            backup = self.filename + Config["backupsuffix"]
            ok = True
            if QFile.exists(backup):
                ok = QFile.remove(backup)
                if not ok:
                    QMessageBox.information(self,
                            "Sandbox - Save Warning",
                            "Failed to remove the old backup %s")
            if ok:
                # Must use copy rather than rename to preserve file
                # permissions; could use rename on Windows though
                if not QFile.copy(self.filename, backup):
                    QMessageBox.information(self,
                            "Sandbox - Save Warning",
                            "Failed to save a backup %s")
        fh = None
        try:
            try:
                fh = QFile(self.filename)
                if not fh.open(QIODevice.WriteOnly):
                    raise IOError, unicode(fh.errorString())
                stream = QTextStream(fh)
                stream.setCodec("UTF-8")
                stream << self.editor.toPlainText()
                self.editor.document().setModified(False)
                self.setWindowModified(False)
                self.setWindowTitle("Sandbox - %s[*]" %
                        QFileInfo(self.filename).fileName())
                self.statusBar().showMessage("Saved %s" % self.filename,
                        TIMEOUT)
            except (IOError, OSError), e:
                QMessageBox.warning(self, "Sandbox - Save Error",
                        "Failed to save %s: %s" % (self.filename, e))
        finally:
            if fh is not None:
                fh.close()
        return True


    def fileSaveAs(self):
        filename = QFileDialog.getSaveFileName(self,
                            "Sandbox - Save File As",
                            self.filename, "Python files (*.py *.pyw)")
        if not filename.isEmpty():
            self.filename = filename
            return self.fileSave()
        return False


    def fileSaveAll(self):
        count = 0
        for window in MainWindow.Instances:
            if (isAlive(window) and window != MainWindow.Shell and
                window.editor.document().isModified()):
                if window.fileSave():
                    count += 1
        self.statusBar().showMessage("Saved %d of %d files" % (
                count, len(MainWindow.Instances) -
                       int(MainWindow.Shell is not None)), 5000)


    def updateGotoMenu(self):
        self.gotoMenu.clear()
        isShell = self == MainWindow.Shell
        self.gotoMenu.addAction(self.createAction("&Matching",
                self.editor.gotoMatching, "Ctrl+M", "gotomatching",
                "Move the cursor to the matching parenthesis"))
        if not isShell:
            self.gotoMenu.addAction(self.createAction("&Line...",
                    self.editor.gotoLine, "Ctrl+L", "gotoline",
                    "Move the cursor to the given line"))
            self.gotoMenu.addAction(self.createAction(
                    "&Previous position", self.editor.gotoPrevious,
                    "Ctrl+Up", "previous", "Move the cursor to the "
                    "previous line in the line history"))
            self.gotoMenu.addAction(self.createAction(
                    "&Next position", self.editor.gotoNext,
                    "Ctrl+Down", "next", "Move the cursor to the "
                    "next line in the line history"))
            if self.editor.classes or self.editor.defs:
                self.gotoMenu.addSeparator()
                if self.editor.classes:
                    i = 1
                    classMenu = self.gotoMenu.addMenu(
                            getIcon("forward.png"), "&class")
                    for text in sorted(self.editor.classes,
                                       key=unicode.lower):
                        action = classMenu.addAction(text,
                                                     self.gotoClassOrDef)
                        accel = ""
                        if i < 10:
                            accel = "&%d " % i
                        elif i < 36:
                            accel = "&%c " % chr(i + ord("@") - 9)
                        action.setText("%s%s" % (accel, text))
                        action.setToolTip(text) # Stash class name
                        action.setData(QVariant(0))
                        action.setIcon(getIcon("forward.png"))
                        i += 1
                if self.editor.defs:
                    i = 1
                    defMenu = self.gotoMenu.addMenu(getIcon("forward.png"),
                                                    "&def")
                    for text in sorted(self.editor.defs,
                                       key=unicode.lower):
                        action = defMenu.addAction(text,
                                                   self.gotoClassOrDef)
                        accel = ""
                        if i < 10:
                            accel = "&%d " % i
                        elif i < 36:
                            accel = "&%c " % chr(i + ord("@") - 9)
                        action.setText("%s%s" % (accel, text))
                        action.setToolTip(text) # Stash def name
                        action.setData(QVariant(1))
                        action.setIcon(getIcon("forward.png"))
                        i += 1


    def gotoClassOrDef(self):
        action = self.sender()
        if not isinstance(action, QAction):
            return
        if action.data().toInt()[0] == 0:
            text = "class "
        else:
            text = "def "
        text += action.toolTip() # Retrieve class or def name
        if not self.editor.find(text,
                                QTextDocument.FindCaseSensitively):
            if not self.editor.find(text,
                    QTextDocument.FindCaseSensitively|
                    QTextDocument.FindBackward):
                self.statusBar().showMessage("'%s' not found" % text,
                                             TIMEOUT)
                if text.startsWith("def"):
                    self.editor.defs.discard(unicode(action.toolTip()))
                else:
                    self.editor.classes.discard(unicode(action.toolTip()))


    def updateWindowMenu(self):
        self.windowMenu.clear()
        shell = MainWindow.Shell
        if shell is not None and isAlive(shell):
            action = self.windowMenu.addAction("&Shell", self.raiseWindow)
            action.setData(QVariant(long(id(shell))))
            action.setIcon(getIcon("icon.png"))
        if (hasattr(self.editor, "results") and
            self.editor.results is not None and
            self.editor.results.isVisible()):
            action = self.windowMenu.addAction("&Results",
                    self.editor.raiseResultsWindow)
            action.setIcon(getIcon("window.png"))
        i = 1
        menu = self.windowMenu
        for window in MainWindow.Instances:
            if window != shell and isAlive(window):
                text = (window.windowTitle().replace("Sandbox - ", "")
                                            .replace("[*]", ""))
                if i == 10:
                    self.windowMenu.addSeparator()
                    menu = menu.addMenu("&More")
                accel = ""
                if i < 10:
                    accel = "&%d " % i
                elif i < 36:
                    accel = "&%c " % chr(i + ord("@") - 9)
                text = "%s%s" % (accel, text)
                i += 1
                action = menu.addAction(text, self.raiseWindow)
                action.setData(QVariant(long(id(window))))
                action.setIcon(getIcon("window.png"))


    def raiseWindow(self):
        action = self.sender()
        if not isinstance(action, QAction):
            return
        windowId = action.data().toLongLong()[0]
        for window in MainWindow.Instances:
            if isAlive(window) and id(window) == windowId:
                window.activateWindow()
                window.raise_()
                break


    def helpHelp(self):
        HelpForm(self).show()


    def helpPydoc(self):
        if not QDesktopServices.openUrl(
                    QUrl(Config["pythondocpath"])):
            QMessageBox.warning(self, "Sandbox - Error", 
                                      "Could not start web browser")
    def helpAbout(self):
        iconLabel = QLabel()
        icon = getPixmap("icon.png")
        iconLabel.setPixmap(icon)
        nameLabel = QLabel("<font size=8 color=#A0A000>&nbsp;"
                                 "<b>Sandbox</b></font>")
        versionLabel = QLabel("<font color=#A0A000>"
                "Python %s on %s<br>PyQt %s - Qt %s<br>"
                "Sandbox %s</font>" % (
                sys.version[:sys.version.find(" ")], sys.platform,
                PYQT_VERSION_STR, QT_VERSION_STR,
                __version__))
        aboutLabel = QTextBrowser()
        aboutLabel.setOpenExternalLinks(True)
        aboutLabel.setHtml("""\
Sandbox provides facilities for learning and experimenting with Python,
and for creating and editing Python files. It is designed to be easy to
learn and use, and to provide a PyQt-based alternative to IDLE.
(If you need a full-featured IDE, with support for debugging, we suggest
you use <a href="http://www.die-offenbachs.de/eric/index.html">eric4</a>.)
<p>
Sandbox's home is at <a href="http://www.qtrac.eu">www.qtrac.eu</a>.
<p>
If you want to learn more about Python GUI programming with PyQt (the
GUI library used by Sandbox), you might like to buy my book, <i>Rapid GUI
Programming with Python and Qt</i>, ISBN:&nbsp;0132354187.
<p>
I hope you find it useful!<p>--<br><i>Mark Summerfield,</i>
mark@qtrac.eu""")
        thanksLabel = QTextBrowser()
        thanksLabel.setOpenExternalLinks(True)
        thanksLabel.setHtml("""<ul>
<li>David Boddie
<li>Phil Thompson
<li>Shriramana Sharma
<li>Benno Dielmann
<li>Christophe Kib
<li>Gerald Senarclens de Grancy
<li><a href="http://www.kde.org">KDE</a>, from whom I got most of the icons
</ul>""")
        licenseLabel = QTextBrowser()
        licenseLabel.setOpenExternalLinks(True)
        licenseLabel.setHtml((__license__.replace("\n\n", "<p>")
                                         .replace("(c)", "&copy;")))
        changesLabel = QTextBrowser()
        changesLabel.setOpenExternalLinks(True)
        changesLabel.setHtml(u"""\
<ul>
<li><b>0.9.9</b> Updated with David Boddie's patch to account for a
change in PyQt's behavior
<li><b>0.9.8</b> Fixed a bug in the syntax highlighting.
<li><b>0.9.7</b> Changed the import style. Fixed a syntax highlighting
bug reported by Gerald Senarclens de Grancy.
<li><b>0.9.6</b> Minor code tidying up. Now GPL 2 or 3 or later.
<li><b>0.9.5</b> No changes; done due to a problem with PyPI.
<li><b>0.9.4</b> Added the ability to open the Python Documentation in
a web browser: all the relevant code was provided by Benno Dielmann.
Also optimized the comment highlighting slightly.
<li><b>0.9.3</b> Improved the syntax highlighting for comments at the
cost of a little speed.
<li><b>0.9.2</b> The input is no longer executed when Enter is pressed
on a blank line; this makes it possible to enter blank lines for the
sake of neatness. To execute, press F5 or Ctrl+Enter or Ctrl+Return. This
change was suggested by Benno Dielmann, who also provided bug fixes for
the command history and for the Find dialog's Close button.
<li><b>0.9.1</b> Changed to GPL 2 since GPL 3 isn't compatible with the
GPL 2 libraries that Sandbox depends on; now any file can be opened with
file open.
<li><b>0.9.0</b> You can now execute files (and set their command line
arguments), and stop them if necessary. The Find dialog now remembers
previous find and replace texts.
<li><b>0.8.1</b> Removed Todo tab; now keep todos as comments at the
end. Improved completion behaviour.
<li><b>0.8.0</b> Improved Goto submenus and Window menu and submenu.
Implemented Find Word at Cursor.
<li><b>0.7.2</b> Changed a couple of default values. Implemented Open File
at Cursor.
<li><b>0.7.1</b> Fixed subtle bug in Goto class and def regex. If a class 
or def is not found (i.e., it has been deleted or renamed), it is now 
removed from the Goto menu.
<li><b>0.7.0</b> Implemented Goto menu, including Goto class and Goto
def submenus. Fixed subtle bug in Goto Matching.
<li><b>0.6.3</b> Added key bindings to online help. Improved Goto Matching
and completions. Implemented Ctrl+\N{UPWARDS ARROW} and
Ctrl+\N{DOWNWARDS ARROW} to move to the previous and next lines in the line
history. Switched off line wrapping for the input window and for editors.
<li><b>0.6.2</b> Added Changes tab to the about box. The shell now uses the
Python executable in <tt>sys.executable</tt>, i.e., the Python that was
used to run Sandbox. (This is useful for those with multiple Pythons
installed.)
</ul>
""")
        tabWidget = QTabWidget()
        tabWidget.addTab(aboutLabel, "&About")
        tabWidget.addTab(thanksLabel, "&Thanks to")
        tabWidget.addTab(licenseLabel, "&License")
        tabWidget.addTab(changesLabel, "&Changes")
        okButton = QPushButton("OK")

        layout = QVBoxLayout()
        hbox = QHBoxLayout()
        hbox.addWidget(iconLabel)
        hbox.addWidget(nameLabel)
        hbox.addStretch()
        hbox.addWidget(versionLabel)
        layout.addLayout(hbox)
        layout.addWidget(tabWidget)
        hbox = QHBoxLayout()
        hbox.addStretch()
        hbox.addWidget(okButton)
        hbox.addStretch()
        layout.addLayout(hbox)

        dialog = QDialog(self)
        dialog.setLayout(layout)
        dialog.setMinimumSize(
            min(self.width(),
                int(QApplication.desktop().availableGeometry()
                    .width() / 2)),
                int(QApplication.desktop().availableGeometry()
                    .height() / 2))
        self.connect(okButton, SIGNAL("clicked()"), dialog.accept)
        dialog.setWindowTitle("Sandbox - About")
        dialog.exec_()


ICONS["actionrestart.png"] = """\
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\
"""

ICONS["actionrun.png"] = """\
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\
x4wyAAAAAElFTkSuQmCC\
"""

ICONS["actionsetargs.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAABl0\
RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAASRSURBVFiFtZfNixxFGIeft7q6\
e6Zn52M3LAl4MBjUm5FIbvHjX8gxf4CCB88J4kFB1BWiCJ4UBD2LOehBzNW4iRjIQkSMIWRR\
Me5G153J7Md0Vb0euucrbrI9ktQwXUXRvL/n/b1V1d2iqlRt6WfxKUReFBURBRMMBiMxViwx\
kUZyp9/7qvfK1rtVY9qqN8af2sbJIyc/OH309GJiEgJKwOPwOBxOHB7PhZvfPtN+s/Hl5mv9\
n6rENVUBEBaPHThWr0mNoAGnObnm5DogDwNcyMnDgMMLh2vAo1XDVnZAgaCBQRjgcHgCjnzU\
O/WFF8FVzmkmAAF88LjgGP5KSXIcAV/0ITwcALQAGDvgcerw4qeAvPqHBSD44DUPOU6nHQgS\
yMkLgOCR6htrhhIECMGT+3xKfNSXTnjvKAr2wAEE5z1DB4J48qETMobw6osV++ABIHivuR9M\
ZF/ugOGMlLtgFoD6h+mTrbT50YlHnl1UVJVAoBgpStCgAeX5Qy9EC+lCkntXHj++lHbjq3i6\
vgdz+k7n/bnXRYEAIEgABLRcIOJky/wjL1ujZunsifeee3z+CXzweC2y8BrwweG1DF720w5M\
7ADxOHEsb10w/rge1ShABBoBkaIRqNVyTlEHjXPpko3Vdh5rH8GFvBT2uBLEh3KraVHbKcHR\
uDwFxHG59wOXNi4hpshaUQTGVxnOCVgFQ9ui/CfrkejIkSHAVMVHfT/c4fz6N6z0V9BIIRIE\
nYIAQaUQH0EAVp3qwA8K8buzLk++Yjwsw1h8bfdPLv69zEp3BWdyiCgDDyXugphwQFFQsKiS\
h3xkswuOMCqDHzsSfHHeq+OX7jUuri9zvX99VNNh1ir3gZDJ0kgJ4GHH7wDsmXXhRuD29jrX\
Nn7m+1sXub17u8g2ogw/IShazhVtCkImylHuVSsKy398x/GDx3Gl/Vv5Fje7N1jt3mS1t8pv\
vV/pu/70BvaTwhNjEfZYfnuuCRSseOGTHz/m3PXPSaMaQT1r22v7nyB6DwjZu/6jOZmEAIsW\
w43djf1Fq0DIvRfhsESjuQBWHOfDZnhKEmne7wQVgBgrVqafNHdDBJC+5BgFI4hR1AhqKM6H\
SFCjmJ7pkct5UVUOvNp6WkUPjZX2yBQOypwsmQU5uBdgalPiOMFsS9691n0DuLyPf7fWz25e\
sQB/vdW9ss/NHDjTOrzXcz6zGZnNqNuMxMZoEOnSvbx+dvPr/WLCjI/jSQBBaCVtWkmLRtwg\
izPSKMUFx42qQWcC8JRPtqJ10g6ddJ5W2qYZN8nijHpUZ8dvzyA/yyvZRGsmLdolQCft0E7b\
NGyDepzRc93qr0P/ByAxCc24SStp0U7bYyeSFlmcEQ2imeLNDFC3GVmc0YgbBcgERDNp4nce\
1ltx2Wo2pR7VRyBz8RytpFVCdOgnd2YqQfVPM8CIwZqYOIpJTEIa1ahH9cKNpEknnSeLs5kS\
mgVgnZxdgyGSCGvs6B9HBUwjzljrru0Aq1WDyiyf54tn2qdMZF5KbWriKJYkSiS1NZPaVGpx\
zUQmkqu/X/1i7e2Npaox/wWeGylq91mxwAAAAABJRU5ErkJggg==\
"""

ICONS["actionstop.png"] = """\
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\
AABJRU5ErkJggg==\
"""

ICONS["next.png"] = """\
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\
"""

ICONS["previous.png"] = """\
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\
DmAH5qz1OP0eJWjqqRCVduEAAAAASUVORK5CYII=\
"""

ICONS["forward.png"] = """\
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\
J4S73uX037syRqkZVn5MAAAAAElFTkSuQmCC\
"""

ICONS["editcomment.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QAAAAAAAD5Q7t/AAAA\
CXBIWXMAAAsLAAALCwFtBIS3AAAAB3RJTUUH0woNCgsyxhAJwAAAAqxJREFUeJztlrtuE0EU\
hr/N5oKxg5NIBJCAnlfgAahGNCloUyAKpPAyUYpUTiqUggZNR5Qn2DS4oEjDRVYcDPgWO15f\
dilmhp1sxs4ig6DwL608Hs3M+c9/Zv+zMMMMM/xjeFPujzOsWQSG49bOuyY3DzZjgOP28Wr5\
ebkFRI5lnhDi2uhSyjWgBfRcJFwEPIDtjW223mzVy5SX9eZhap0vpVwHHgBr+ixb0VjvuQ98\
0eNBFgLzAEeNI3Y2duCA9t6zvRWgkyLhCSG+OvY7IaXM4SjFWAVqgxqHjUNDouEgEWl57wJF\
x1kxqnQ9oAkU9FzfJjGWwIK3gO/5VMIKuxu7ThJCiB+OTB8DIx081ufd1P9DVBkmEgAgF+fw\
Y59qv0p9ULdJFIEuEEspV4A7OjvfyrCjfw0JEzwkQwmofKiwP9onX8yTW83RP+9z8vqEoBQ8\
AW4DVaAvhGiMS0CrUSCpe6SVuZ5A87RJoViACDrNDmfvzghKwUtUrZeB78BAK7Cu5+ZSCvSA\
JZLbn90Hon7EsDHkggta71sEpeAVyWVqpw6MrQeU8cwBN1ClGupnlJkAQxh1RnQ/dwlKwZbO\
6BT1PtdITGViCVJwOqKTQNgMCZsh5bflF6hsq8BHTaKrs5nL4oQG4xzR1QsWgXvAI1TNG8An\
Hdz2gXlgFXhI4oRpmEADoI5SsIHliOM29YBvqHrXgDMyOqGU8imJD9gknHAp4KEu0LIemxt9\
pRcAt7jshDHqXU/7gEkqUwnMvK/HEe5u6Ash0qR+QUpZtEhA0pwuKTLN94CPckCXE7aBc/1r\
k7iCqQhMUsBASrnEBCP6EwrYTuiR1DxEqWArkemD5HdgPD6yghssAHk9vtIFDaZRwEN5Rp7E\
fs28CWS6YOdvEDD7fSu4C84uOMN/g5++gjuED3GGqgAAAABJRU5ErkJggg==\
"""

ICONS["editcomplete.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABGdBTUEAALGPC/xhBQAAAAlw\
SFlzAAALEgAACxIB0t1+/AAAAUBJREFUeJztlrFKw0AYx38RhzyCY/oUqVskm5tEcBQEFynk\
EcQXKBS6SKDg2KG46ChmbJ7CjL5BXKQd7gvlzgRbm3An+ofj7rsj933587/7n8ciBICkUL0Z\
94Qw8gE46DXLFvDMichfaHH+kXSb0WDYKQZWNnI7xcB2uBNN3OpaidMRAC+TqRZ/3p8AUA1f\
ASjyqfadfQYCGZT9a6CRbesMHIbXVwCU2cwDCGSh3HNjUxM1LiTfPJsBDjDgpTKY7K+BnU7U\
H/YCAw4wsHGnfy/4GVpeUL/HC4byB8v+NeCoFyzjUxkWjRWG0ZFazd9lpr4nurkfrDNg7U0Y\
pyM37oGvOE5UE1xK+x6+tN1gnYEuNKCdnsG56t+e5LQYbmquu8PAmVT2+CwVV6rCyA9UfFMC\
kI+bN6p18tCWqcUzrDOwBh2zVCR+JZVeAAAAAElFTkSuQmCC\
"""

ICONS["editclear.png"] = """\
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\
"""

ICONS["editcopy.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QA/wD/AP+gvaeTAAAA\
CXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH1AcZDRI4gmRrggAAAvxJREFUeNrFl01v20YQ\
hp9ZrhJANRDHhZWDfCjinOLCQOv+gl7aY6/tb/Mhp/bav2FYQdt7HPTgXhOkjdOQ3JnpgTRN\
WqQlWiqygERhuR/vzr7P7ErcnU9ZIsDri79GqTg7X/DTjz/IppO7e/V18erS1y0Xry79zZu/\
/edffvVtCAh3vUylkn8seP/+A2/f/sO7d1fN++l0erkNEWFVAwmBmGXELOvUH395dLCzM329\
qYhBASKCiBBEQARptdzd3WHv80d88/VXTx/vPvpzExHxTnWZoMkRIGYZqomz8wVn551mX9TP\
E+DlVgU0kQgBTQmA77/7FlPn6uqKD//mAPz2+x/8LxHoREOELBPMIM9zylKr+lDtzenpi8XR\
82Nms9kobFeaMGQ3PlB1irykTIkQAg8mEyaxWsN8/oTDZwc8PZx3PtdRG/LJSgGaDFUlz0uK\
osDMKipiIIuBGKshVJ38YzEa2zCUAzQZmgxzp0wJU8XdKzJCIMZIzDImk8lG2Ibe9FiH3twp\
ioKyVMyq/Q6ZkMVQ/Q4BEanN6vfCNva5HqAoEkVRoOq10Qw8IATMFYITqATd7jsG214KUqmk\
lOoVgXklwswIwXGrJw1OkKwT/rHY9m6BqrZywFKIkFa3mkLcpRdb6Md2UIAmw+sB2oO1O4dw\
E+4bXT4K20EPeJ8nghOsMmVTT6gmbQlxs0FsTSqiwi3hcYiClWc51o2cKmbD2F57KLuF55IA\
MwP3ZrXujhud1Q+dGX3YggGCW5eUXgHN6kXAfSkaZlY/O1eqJhOWZTkK2yUBIsLDh93MZnoj\
xNyrMDdCjFibSlWbRLQuto2AKlksNr7hNtjqMraOdrDtCKiPypN1Jzo9fbGYz58AUBYJNWPv\
8V5zLixHAdyk1+DtLVj7NnP0/JjDZweYOkVZoqpM4gM+25mOwnbUhaRdZrMZ+/v7zZnRJmcI\
49vYrn0fWFXui+1WBHSw7Ulid2G70RZsA9uNBGwLWwC5ztf3KCebTu7uL+VT/z3/D4ypWLEx\
98aLAAAAAElFTkSuQmCC\
"""

ICONS["editcut.png"] = """\
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\
AElFTkSuQmCC\
"""

ICONS["editfindnext.png"] = """\
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\
"""

ICONS["editfind.png"] = """\
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\
RK5CYII=\
"""

ICONS["gotoline.png"] = """\
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\
gg==\
"""

ICONS["gotomatching.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABGdBTUEAALGPC/xhBQAAAAlw\
SFlzAAALEAAACxABrSO9dQAAAYNJREFUeJztV9GNhSAQHMw14LZAC5agNfnLrzX5SrAFW1hL\
4D5UsiIgenrmkpvEBAVmBtbsAvCPCAyMNTD2FZ67xC/x3S1+ivcp8RR/ITufEg4Z2RkQneos\
ITMH2znche8ohXEcAcDKh5lrInJjlrYcg7ZtQ2asM5ApbrXWO6NE1AMAM9dSVMB2XRfl3RiI\
bT8z11rr9VWJZ2dkGd94/c6Ur1HkbL9Y5WZy3ztNyaGI6IP9TuxgYGx2CJi5kbGO4PQPnG1g\
WdUGTdOkxFWi77SB5MrKskzNS87N3oEUpmnCMAyX5t5iAICqqurXDdySui8bSMT9VgOhzAZg\
jnvG3B8ZsJH25r3ve5mQALi0nIXiQvXLzpxHMDDKrwUxciWKjfsGzMnIS0gWmDNnqDT7Gl8J\
g0oIWpmGl2ID8W1DOo4jpmn6iAIWxXoeiIUhlF4VEX2IyBnxx2it1ZH4qhk6EflhCJZfwNUH\
lRpzwL05E56uZFeR1Hr1WP6UiVdvR0/fNf4+vgET3cb2N0kZDwAAAABJRU5ErkJggg==\
"""

ICONS["editindent.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAABGdBTUEAAK/INwWK6QAAABl0\
RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAEgUExURf//6f7IjP//3Mynfv//\
2nhfQv//7f//+4BlR/vQotqyh9+zg7KOZ/7HjP//0sqlfbiTa//0v5h5V6GBXtKsg/jQo///\
/aCAXf//6oFmSHlfQ//msMqmfdOpe//xwty2jIxvT////+y7hv/erf/Tov//1s+pgNqte//W\
nv/6x+GygOa3g/vKlXthRMSgeMifc6GAXY9xUf/2wv/bo/nEi4ZqS6OBXf/tvui9jrCMZP/b\
pP/1wLiSacafdN+3i///2+rCl3pgQ//3xdKoe///9aGBXY1vT//5x4ptTdqtfIltTcWhef//\
4dixiP/KkP/bpvrIkrGPav//z559WdexiOa4hvzQoP/suYNnSbSQaP//2I5wUL+Zb5aWlgAA\
AP///9v++JMAAABgdFJOU///////////////////////////////////////////////////\
////////////////////////////////////////////////////////////////////////\
////AHNt5EMAAAFCSURBVHjaYognAAACiCE+Fi+IBwggBkImAAQQQRMAAoigCQABRNAEgAAi\
aAJAAMEUxCGE4pBBPEAAwRXE4TABIIDgCjTisJsAEEBwBcZh2M0ACCC4giB/+ThsJgAEEAOM\
zy7toIbNDIAAAipgYGNi8WFXFOQUYY7DNAEggIAK2MQY7JkkXIxUfJmZMc0ACCCgAiYGPk0n\
d2srHS5+b704dBMAAgiogCUq3I+RkZHXREs/UpgH3QyAAAIqUJWzsBWIkdVWDzbl4MAwASCA\
gArMQ8QNo4UCnW0ipFgx3QAQQEAFdq4KHm4GMtxmuqxYfAEQQPBwEA31csQWDgABBA9JZU9J\
rCEJEEBwBQGW2OMCIIDgCpRwxCZAABFMDwABRDBFAQQQwTQJEEAEUzVAABE0ASCACJoAEEAE\
TQAIIIImAAQYAFmFY4BPZteNAAAAAElFTkSuQmCC\
"""

ICONS["editpaste.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABGdBTUEAAK/INwWK6QAAABl0\
RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAVESURBVHjaYvz//z8DCDAyMjLg\
Aq2t8xYwMTHFQ3j/GaBawODv33+XT5zY47V16/IXQO4fBhIBQAAxgBzwH9lENFBTM33B9Olr\
/3///vM/NrB+/f7/lZWTr5uaOqgClbOSaj9AADEih8DNydoCf//9N/z15z/Tn7//GVe8yoiV\
khKLS0ryZeDkZMdpyNq1+xhOnrx8U+P/6kp9iY9f2VgY/wHNuG9VdfM+OMggGCsACCC4A851\
axmysTLuY2bnFuAUU2R48oGPYfcjE4a0tCAGDg42gj5ZsWIXg9CPYwyWCs8Yfn18xfD702uG\
p29/5bm33J4DlP4JxP+w6QMIIBYY488fxvVC2iYCCl6eQN5vhl83fzKwrWFi+P37NxgTAry8\
XAw8ssoMCn5GYP7byxcZvm3dPinbXez81J2vzgKFfmALCYAAgjvgxy8GeRl7HYb/f59CEtef\
PwzfvvEyfPr0jai4/Pr1BwMP10eg/p9gvpCGBMODo0IMPBwfdIDcm9BQwHAAQADBHfDt538G\
JpY/DP+h6Zid9S/DnTtPQDkAZxSip924aA6g/l8wA4GeYGD4/P0fKP5AmAlbNAAEENwB34EB\
BNcMBPLSDAzL5rGTnqvgDvjG8APoqV+/GRihlmPN5wABhBICyA6gCPz9B4oThp+//jH8/vMf\
r1KAAEIJgX9EJDaiwEdgugGa9ePnP1AI4AUAAUR2CPz6K8Lw5ZcCOB38+wcpzP4D6X8g/ufv\
YDazjDSDTRCXzfITZRtxRQFAAOFMA4TA5x+yDOyCXgzs7OzwBAlyBMgxf0X/AbP1PwZ9mX8M\
TJfvhCxatJk1Ls43ERQ5UAwHAAHEhAgBiAOIxf+ASRxkOQ8PNxjz8nIz8PHxMPDz84BpCOYG\
1RUM6uqq/vPmbQRlJz4gZkZ2AEAAwR3wAxwFv4nG/4DlxP//hEMKFBJ6ekpAR6gEzJixHsMR\
AAEEdwAo7nD69tdPhn9fvyHwxy8Mf4FB9p8IF/z9+x8YUqwMRkaqDJqaKgGTJq1BcQRAADEh\
K/4HsgwZAxPGv1cfGP49fQuhYfjdJ4Z/334SlyOBUQCq6UGOMDBQZpCWlgro7V0BdwRAALGg\
FiKIPPP/M9CCz7gt+ctEXBTw8nIybNp0HBwSIMeAaCEhkQCgVAUoMwEEEAu2Uuz/R2CW+Io/\
R/xj/ktUFBgZqYHTwY8fv+Hqb99+BqL4gfgVQAChOuA3MM5/AH328TtBg/8xExcCrKysQAf8\
ZmBhYQFnUaSkB7KbCSCAUBwASmz/X39lIMbkv2AHEFb3+zckpEANHiYmRKEFAwABhOqAj0DL\
fxNXGP378xevO/8A5X/+/AO2EGE5A9wRMAAQQKhR8OErJD8Sk7pZUEMAZOivX3+A+C/YcphP\
QTmAiYkRyXLUAAYIILQoIL4oRg4BmMUISzF9jOwIZIcDBBDWXECUA/7+gVsOylqYljLgdARy\
CAAEEIoDPnz8y8DP9Y+4KPj9BxzUkBY1ZjDjcwSyAwACiAXRhvh/dNMpXmsL1c/A5hjhdPBB\
BOIT5NRNrCOQowAggOAOuPLsU/jPPzxTXn8SDCAmBMT0OBgMMHxOnCOQQwAggOAO2H3j5Usg\
TgEyK6HlNAs+B9RbFwLVMiYSSnDYaOQQAAggZEtAqeoDtP3Ohl5RoQMeHsH3IIOwW4bfEcgh\
ABBA6L4EpaqvUEygiOX4ATOIVEcgOwAggJjIbXeCKhjk/gLIMkh0INMQS9HFkaMAIIBYyG55\
A6vWy5cfMzx48AbeFkTGoLLhH9C7mGL/gR2el3BzAAIMAPtmf2zDNnayAAAAAElFTkSuQmCC\
"""

ICONS["editredo.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QA/wD/AP+gvaeTAAAA\
CXBIWXMAAAsSAAALEgHS3X78AAAAB3RJTUUH0wkCFTMtVD42BQAABCFJREFUeNrtl11oW2UY\
x3/nJE3SNm3SJnWtG7O4mVZwraI4FaGdE2HshTlYBwoylF3JoHO7ERkKU+cQtRNleKGzMEHm\
xRwmaje6MqT1wjmc1Ora0u+1TdKvtEmaj5Nzjhc7tqZNY79gF/aFl0Dy5Px/7/N/eN7nSLqu\
czeXzF1eGwAbAJIQImtAW7XXiYX9WHhelqgBHAtjNJ32VJzW8FTsE9F7sBtQAX1NAFfdXicW\
XpOt1MsSjuOPdbC11E5VuTMtLhiK80dfiPO/l9AfKSYe5YIS7D4u9GN+A2TlAJeLvPtlmS+3\
2EOOo89M8mRVGS5H7n+epuX6IKd+KGRwxjmsRAMvieThNkDJlo1FAD86vY2yxKGXH/mLg89u\
J9eWsyJPp6ZjfHwpQMtAeVgNDxwQ6pGfgMRSEHMAvsLvnMA1oPqdvbfZXOpieDSAoii0D0kA\
lDkU3IVmStwuStyuJSEUReGsL8jPQ6WjjLXuFrYPeoBkpljzfCWlGgtsavWBh27z7Y08boxa\
ga2Qmm0HLYKW8mOybUM2b0Iyb3qgeJy6R6OUlN2X4bE57N1ZRHtQKQs7q04Q5ygwmakmJCEE\
vvxvziDJ9fNHmGkmHmwT0uvXjPQl/uWlyae8uQP7/S+SY9+zrTjKvicKMJkXW3Wrx4+3owj8\
zY8L+2d/AtFFANTN7EKSW+5kIXmTiV8+FPmf9gHTQBiYNdKnGQCykbk8n3pyJ/btjcWFZvue\
h01okiX96WqSr9sUSIyfEeqR94CJhVmQqAvdBKpRZr4QqVfPAyFgHJgxTp4yxNP/dwfC5tNP\
P03elgsmq6PguR2LzWjthHAo0CaShw8Bw0A8vQa0VBHJyRNCP9ZsiAeBiCGcsXJ91nO16JoM\
SKhxCSVyTtVS9V1+F+Xu9Fi7DcKSudqnnqwlxxnEnBeb+1HXQpIQwg6UGKecNHzSlqpwn+Xz\
ecsWll5eCU950r8bD0NHz1jWRmQGLIZoMpv4P/eHz3z2KyTzC5vvLWOre+X9/9deUCKjEA+e\
Mnk8Hs2o8NRy+7dH+/5KF7srw5Hog4rsIN8Kqra8fb0X1MgQxEYahPktr8nj8azmElM9etPl\
Lm1XRTQSrkzKRdhtoOnZ92/9KkQGIO5vEDlvXwRGVwugA4qHK01dWk1FLDpdOYuLgtylxdsH\
EhDth0SwQVjevQiMAoHVAsxDSM1NXVpNRXI2VBnR3RntuDUUg+gAxAMNwnp6ThyYXetAogIz\
Qn7jFbTkpdh4J/1jkFLnd/dQGKKDEA82CNv7aeKAth4TURqEMtXJ4AQkU9A3Mg2xkSXFAdZi\
QQY7rjZ1abUVeiJUGY6pkBjPKr7eM2FaJkiGIB78KJv4smbCVSwTUAjcA+Qal9pYJvH0eWCd\
M2F0VZPxuWSHlTbeDf/3AH8DCP0QxXmU4WYAAAAASUVORK5CYII=\
"""

ICONS["editreplace.png"] = """\
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\
NjGv/Ac1w6RWgpLp/gAAAABJRU5ErkJggg==\
"""

ICONS["editselectall.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QA/wD/AP+gvaeTAAAA\
B3RJTUUH1gkMEiAZoThzJwAAA2pJREFUWIW1l0trFEEQx//d88g+XGfHSGJiWHyggrrm6N2z\
4MFDwJvkKwgePIsY/CqCBz+IJwXxkE1AiJpssjgxzs7038O8H72zUVOwbE93Tdevq6qrewRi\
ISlev3n5kEQLZyhC4OT5sxfvhRAEADMZ2Np69Whj48lbt39BniXAeHygtrZePQbwrgBAyY7j\
9GWrtXAmhkkCABynLynZSfpN7Rv/2XgCALAwdqYAkeHIaAZQlFqA3f1fGHvBv5guAQB317og\
y+vXABwdh/g82tNO3+1GIfS84wYAwHGcqH25gzonaEMwGo20AIPBAACws7Oj1UlkOBwiCQEZ\
U80D0CSu68J13fiJuXnL7Wo4GgFMA5AMtcZtU6BlZeWiODmTAIAU6C0YWHas0wEEIaCEoQXw\
A2LineD42IsB8qORIdu20G634bRNXOxZUQKS8yXhPOJ53swccBwHa2traQ1IAMoEfw3Q7ztw\
nGH8NDsHCgDzFCLLELh57UrNSOTCbqcL25RZtCnieQlCAACuL7VAMtLLAQhRnLEWYBoq+ArI\
7+c8xO/JzypYTqfT6WDx3Lks7nkPlAi0Idje3tYNNcpgMKi4PfUAGgCSF9bX782Ia1m/2laK\
ub5TJCFJSAEsmDI7SKK/eDxZQbk/DRhA4NPXqEyfbxu4dN4swOgBYsogJPZ+HNQUjmoxqTvl\
SOJ73L660sdyL6kpVd2SB5hSjkbNdX4eubrSTw3XwdaGgCSGw7univvnjx8AAjdur5d0sjtB\
VqY1AMlhJYWAbchsgmQQ1VgjzuqTb19AErce3C8k3oKZQCTxbyhEJBEqhW/74wLarHxot1tY\
cnsgicWukTNYNN4cAmalc3d3t6Ksk9XV1cKxm7o757q0f55tSAJ37tyea78n7WjTlVeqazcA\
rDgWLnSNXCUrGivfcklgr7zSXLuYhDNyINIjei0DPcgCQN5o3ar29w9memC+WzFjxnL51Kw6\
H+vNzac5nep4XRGqAswwWp24zt11q643rAGoGtUnlL6vadV1APZkPMHh0aFy+25622SlUT8p\
Nf11cjgeq8l4AgA2AD89nJPPc98PukEwNab+1PR935oGgRkEgRmGoaHC0FCKUiklCRYOdgFB\
KaWSUihpGKER/2zLmlqWFVi2FViWHdi26eU/z/8A81bdkxXVzcIAAAAASUVORK5CYII=\
"""

ICONS["edituncomment.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QAAAAAAAD5Q7t/AAAA\
CXBIWXMAAAsLAAALCwFtBIS3AAAAB3RJTUUH0woNCgssPB80owAAArxJREFUeJztlr1rFEEY\
xn97X0m8S9SoRBG1ONMIKYSAVUqFwGCTItglf0D+mpAiVa61sBtIYf4DDwwhELCLFjEemJx3\
8XJ7d7sW74y77leWgIhwDwz7NfPO8z7zzDsLY4wxxj+Gk/HNzzG+Agxz9k1EKeW9o5S6crDW\
ehb4AVxGSSwdLNXqR/UOQGO1UQZGSUTTCJS01nPAI+C26RdWy0cyfwh4wMA8/0b9qN7ZXNlk\
490GwCzQSSIaI6CUyi2n1voFUIiQY+3tmr+1ssXe+Z599Rj4YkgOsgg4WutJYBqYAW4Ck0mT\
mGAdwEVUiE3eGrTs67tAKyFGnABirBpwwzy7iCc+JCjwLJr59so2x/1jik6RslO2nyopScQI\
+EAfaCPrZQcVtNZPgaoJ5iCmGtns7eT73X36fp+iX2TKn4rOF0MSgQEibVcp5WYNNgoUgEJj\
tVE7XD/szr+Zp1Kr0DvrcdG+wP3kkpR5GgFLYkjghyriA3tvFfBMP7v+5eZO8znwce7lHHjQ\
a/XonnSzcqBwxbcJxIy3EGNWQiRtsxgAneZO89Xp+1N6rR7D8yGe65GFNAXy4j5i0hHimRai\
xPLi+uLuxJ0JWx1SY8Z2QZ4KaKG1LhGoOAJ+AicAzZ3m8sLrhd2rYkTNUUbkthWwnNIPJLfv\
wGfgjKASlhCvPACemHht4MiQ+8PYaaXYwjeT+0qpWDYplXAIXJjJPOAesrVjZTgpMwdx+4y5\
OqYVEANWEWM6ZqI28BU5kEaRWCWCneOT8yzwTScrp6OU6kdZW0QrYQRDxBOX5jnxNMz6H4Ag\
82mkPNutaCthFzg116gCuZDqgTynYqgSXhtpCthDyWZeI1h7B5HSQ9b1G39BgfCpWCXYjuHq\
55l27d+xLAJJp6IlFibgmn7Z9TYDWSZ0gGKoT/SXzF4T3T3Gf4Nfi0P5Rstj6dwAAAAASUVO\
RK5CYII=\
"""

ICONS["editundo.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QA/wD/AP+gvaeTAAAA\
CXBIWXMAAAsSAAALEgHS3X78AAAAB3RJTUUH0wkCFTYqty1X4wAABBVJREFUeNrtl11oW2UY\
x3/nnHy1SZtk7Wo/trVFl6066CpsyMoc4gaCp65leKFebJGhIF7sQkEmrAzKcFgQdjEUNChi\
L8qYnT2DCYrCXBER3HTMNcrsZ9KWJEubpPk6H170dDNt+qXVXdgXnpvwPu/zy/M+z/99jmAY\
Bg9yiTzgtQGwASDIsrzshmt7+v2inYCq89n+gbZXgQyg/ScZ+Lq2369GCRzz3kSf4KXLm/s/\
BcoB6V8H+NLb79ezBN5oucXrHbv44HAYm06HUtYXWE+IogCX3f1+IHDiiZscbH2UUBzqt9bw\
3pFxrBapXXFdWDeIRQBK+Rd+wzAC/pZBHt+9i7Eo96xicx2dz4yCaGtXnL3rAlEAoLgu+jH0\
QHvTCE1NOwjFWWTOTVt58ykToqTnH0NIPp9vLriz149AYF9DnN1NtSQyLGnY3Gx3T3AjXLYz\
KD23w6devALkAeNvtaFS0uNHEAP1VVb27bSt2nl0Ks13t3XQMn1y9tjLwMxaW1Tg+bgfCFR4\
3ex9eO0pHIrAr0PTcxC542uGEDgSWTJtzdsrqCwr/G3gN0gnosUd0qGjsnjycyC52uuwkI+3\
kk8+gp4pLCZnQ1cojsvjLHSoKofhhA7ZWA+52E+AiiAagCFbu64DVkBYCUCxfehHEDstsn7i\
RySCSDhMx7kN+vkXIwn25tRCx1ovDE+6QMsdJjNxRXZ0fw9kzYA5IL1icMv7pzH0U+jqLcnn\
8+nmAbNm6pJAMsihCtTU0xVeNwag6fetym1lctqwYSk9FMw0f+OTrg4C0+YZS3aDIp5rDEpt\
fWAcBR1mRztFc7NmOt63bOwjdJXbYVC1QgN4rNENFpcLR7Wi0B1QtK49f83ggsAdinjuE+AO\
unoAXYX8zAXZdub6cq+hpNB9HsnxSmNDPaX24ptGIpCIjYM2C4Y+BgwDN4BtgBtB3A+AzQP2\
SkiNgJockIW33gbClmWuSiMzcRpH1bN/jITrGrfVYCmid9UeqPbUEUtCNGlsQZ3dgpZpBcC+\
CUkUqHZDLAXpyCAY6h3iP7+LlwgwtdI8ICm5k09i81zC6il7qLqGUtvadCKnwvjkXchMgTb7\
lSydegeIAONA/J4UL7EMn3Q1FMy0/IDAwVQyURZXvTjtQkFRFrNUFkKxPInoEOSnU6TDZ2Xb\
mY+BSSBsFq264kRkFpZdmTneiLPhLJKjDdEyd5/WcuzWwrrLZtKgzkI2Augp8slLJH/vlb09\
IfOfR4HUvFquBmAewgq4leRrzdgrX8BSegDBUkS89RRa7hfyM9dIj30re3umgDhwF0iYWqGv\
eiZcWBNACeAyn2EnYF/wrBuAas6O87qSMrVGWyzFa1uaeVjGvEObCbWw/3UTImfqir5kaje+\
Df/3AH8CAs3OiTI23BYAAAAASUVORK5CYII=\
"""

ICONS["editunindent.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAABGdBTUEAAK/INwWK6QAAABl0\
RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAEgUExURf//6f7IjP//3Mynfv//\
2nhfQv//7f//+4BlR/vQotqyh9+zg7KOZ/7HjP//0sqlfbiTa//0v5h5V6GBXtKsg/jQo///\
/aCAXf//6oFmSHlfQ//msMqmfdOpe//xwty2jIxvT////+y7hv/erf/Tov//1s+pgNqte//W\
nv/6x+GygOa3g/vKlXthRMSgeMifc6GAXY9xUf/2wv/bo/nEi4ZqS6OBXf/tvui9jrCMZP/b\
pP/1wLiSacafdN+3i///2+rCl3pgQ//3xdKoe///9aGBXY1vT//5x4ptTdqtfIltTcWhef//\
4dixiP/KkP/bpvrIkrGPav//z559WdexiOa4hvzQoP/suYNnSbSQaP//2I5wUL+Zb5aWlgAA\
AP///9v++JMAAABgdFJOU///////////////////////////////////////////////////\
////////////////////////////////////////////////////////////////////////\
////AHNt5EMAAAFHSURBVHjaYognAAACiCE+Fi+IBwggBkImAAQQQRMAAoigCQABRNAEgAAi\
aAJAACEpiIPRyCAeIIAQCuLisJoAEEBwBXEa2E0ACCCYgrgwY+wmAAQQVEGcvH8QdhMAAgii\
IE7NQZodJoQKAAIIrCCOWYRTUJHdh4WJjSEOzQSAAGIAyzP7qhi5SDDZM4ixoZsAEEBABXF6\
3vxcOlbW7k6afAxM6CYABBBDfByPcKS+lgkvIyOjX3gUC7oJAAEEMoGDwzRYXVs2RsDWQk4V\
3QSAAAK7gVUqwsY5UCjaUDzEHN0EgACC+IJV14xbxsDNQ8HVDt0EgACChoOjV6go9nAACCBY\
SEp6KmMPSYAAgseFZQD2uAAIIERsKmE3ASCACKYHgAAimKIAAohgmgQIIIKpGiCACJoAEEAE\
TQAIIIImAAQQQRMAAgwAc39jgBib/28AAAAASUVORK5CYII=\
"""

ICONS["fileclose.png"] = """\
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\
AA147xggwADtTBaocZkPNgAAAABJRU5ErkJggg==\
"""

ICONS["fileconfigure.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QAAAAAAAD5Q7t/AAAA\
CXBIWXMAAAsBAAALAQE2cE9bAAAAB3RJTUUH0woNCgoG/r/MNAAABM9JREFUeJztl89rG0cU\
xz+zO7Or1TrR2pKNIIIkoGBoDznkkNxyMSanQo69pOdQiimBUppbCoFiekxskvwNSS6F0FMP\
hRCIHUPimPyASsGNpUiJflhKIq92pwdrt5J/xBZ16aVfGObHzuz7zpv33ryB//EfQww5/k+h\
dxV048YNffz4cYQQmKaJEALDMA60XLlyhevXrysgiMjInnzD8zyWl5cxTXOgSCkPZExKSafT\
AUgCHWAD0EaPgFJK/Uta34ZRIAGYkQYEYNq2zePHj5FSopRCSjnQVkrF7WhHSiksy9pxztZ+\
3wZdoN2TK6IjQErJzZs30XqbncS4e/du3D59+jRSSkZGRpBy8zdaa4QQhGE4ULTW/f+VgNHf\
gX1a/dTUFADVapXFxUVOnjxJp9OhXq+TSqUwDIORkZHYiHchEEH0E9gTWmtWVlYAKBaLABQK\
BYIgIAgCtNaMjo5SKBRIpVK4rotSCq11TGKr8KEI9AteXV0lnU7TaDT48OEDQRBQq9VwXZdc\
LseTJ0/I5XKMj49j2/ZuGhiewNOnTwFot9uxeuv1OhsbGyQSCQBev37N9PQ0Dx48IAgCMpkM\
lmUNT2DrAq01L168iPtTU1MsLi7y6NEjLly4gNYa27YxDINnz56RyWQACIKAbre766Y+qYGI\
RKTCW7dusb6+ztraGq1Wi1evXlGv17FtG4BMJoPjOGitCYIAKSWGYQx/BNGCqERGFIYhyWSS\
o0ePEgRBPN80TbTWJBIJXNfd5gE7GOH+NdBv5f1aEeJvz42ERXOFEHS73W0a3DeBMAxjlwNw\
XRfTNEkmk7FrffHLZ6jvsvi/l5hvfst09Ruy2SzNZhOA9+/fYxgGjuPwqTA/QCBiurKywtLS\
ErVajWKxyLlz5/B9n1wuRzqdRimFPxnw/fjX/Jj/gU6py5kzZ1heXqZYLFIul8nn83ieRzab\
JZPJ7EpiRwL5fJ6JiQkKhQLHjh3jzp07nD9/nnK5TLlcBsCwNT9XrmGsa9Q7mPt1jrNnz3Li\
xAkmJyfj6xzg48ePcXtPApHBWJZFNpvF8zzu3bvHwsLC4MrPBetBCVUzMHv26Ps+Uko8z4vj\
gmEYSCkJw3BvApGxhWEYx/VEIkGxWOThw4cDC+0jmk4L7FqICTSbTcIwRAiBZVmxO/ZfUHsS\
iKz5/v37LCws0Gw2efnyJZVKhfn5earVKr7vI4Tgpz++wmqDWzYwx0yeP39Os9nE8zwcx2Ft\
bY2ZmRmklDiOg2ma+ydw6tQpLl++HI9fvXqVt2/fopRibGwMpRSJJcGhdy4iaGGGIRcvXmRu\
bo5SqQTApUuXqNVqOI6DlHLAbfc8Aq01t2/fplQqsbq6CoBSKr7ldtvNzMwMhw8fxvf9WFOW\
ZQ1/BFEYTafTJBIJhBAIIVBKxdZsdQyO1NP8SYtux4dDm0mN67pIKeOApJRCCDEQOfckEEUt\
27YxTXNgcTRn9svfaLfbvEm/odVqxZdRlKYBA6F8C4GB9AhANxoNZmdnqVQqOzLdCWEYDoRc\
IUR8Ae0DGnqJYY9ICpjo1bLv20FA90oXaABvenVX9n302cxWYchEZQh0ezL8SG60QwFYgN2r\
jb7xg0B05iGbD5L4YdIvQLD5WOgndZDQfXX8NPsLzuabzPO9pmgAAAAASUVORK5CYII=\
"""

ICONS["filenew.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAABl0\
RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAATrSURBVFiFtZdbbFRFHIe/mTnn\
bLdlW9vabUuLbZHYFixoxNQQMFGwkRiR1hgwMTYmwIvGV01QefJFE6I+ob5YuRiNdBVFQwmK\
JYWSGi7BWwu2jS1UehG7S9fu7jlnfDhL71vapvySyezMzszvOzP/mTNHaK2ZqpaL1/qAnGRR\
TGswk5LDaFf3R6OREzXrK+rn0s1IUZ/2UEXQskw12UNDLA7xGMQSXh6PQ+xWHgdbDuS5rvN8\
qKltBHi5tubh6U84QXKmSiFASjEtKSVI8wl8PkGaJfBZAmtibgqUNJzi4DJTSeMlEPtDTW1q\
Jo9ZAWbtIMGywDTBtMCakguJm5FusaJ4ZZqSZh2IUKipzZovwKzrrtQEU3M8N00wFH7LB1kB\
H6X5K/1K+jahxbFQU1v6fABuK9NImk+ZDSGQPgv8fggsMSnOrfQr6a9Gi+ZQU1vWogHAzEsh\
pLdMfr+XMjIMglkVfiUCVVqL1lBTW97EMVLtgjnLNL3doV1wNSgpaDnfyeCNiFc/lrSltVuB\
EKcbGhoq6+vr7UUBkHIChIbiYDary7MBuHkT2jvAcbz/wiPDnGs/mVfgZw/w5qIAQDIoTXBd\
LwFE/4POLm9LK+UBSOmVJz3AYgAAGIYXE4YBo6PQ3e3VW+ErKGcEpTyQqVo0ABifhZ6epPlf\
JygLv0Je06NIHNQMbosKMDo0QN/hvTj/dGIoED2nyKjZSO7j5cQjV1EKigdOm0UdjatmB9A4\
8zWPx6Gv4XXKnh6k8Oou3N6zk9ZbKbirdTfPPRNOX7c2UdtYI9amBBBCpEciMDLivWhs2wui\
VBoZgYEBcIofQUcjZG3dSuGN3ajrF8baZLa+xX1bfBjllUT7huKNXfRAql2QJLdtSNjjWwzG\
I1m741Fv2159+vqddH33GmVPdpBVuxXpfu4NZxmU1uWiikoZ+vQL/dW1Bw4duHz2emqA5JQp\
g0mHCcncdSdDKQVu/2USf7fjL9tA78fvULxDEHh2O7g2vvvXoKVFeP9BfvjtnnhJYDjt8nax\
eYlJs5jpQtJ6qS+6annQbyg1ZjpbSvx+nCWJ9/GtqQLXAxVCIrMKQPkA0JEh3OGwd3FxgYTN\
9Y8O9aaeAQmGur251pCQEnc0ngwWz0DLqZteg2N75i5o28FJxJ3Zl2COAOlVGwl3F9B/oR2t\
wTyzl6U7qtGASETRdhzhzyR66nuOni+MSeV+k3bx8IFPOmhJdQ5o71Y0DnK7lL18Ffnr6gj0\
t7B0VzUqv5TIZwfBTRD/5RJ2ZzuB7duoeXDQUln5w1uO6a8bu/TgnA6iVDCG4QWqkSzHmveR\
s0mjgiUMH25ksLfIexrboft4DPvPdnK21YnHgudf3LdBZMMCTsKpMMYEoFjXzwhp8O+XjQzf\
+zbpJVVj/TI2v8GVn0zily6SVpBnGpIVCwKYDSj3hXe5dqaYxNoPKVqzDimTB4rWSCXwP7WH\
hm+D0SMnRWhnM+dSAuixW/78ZAWyWbblVYLLy1EK/JXriRw5ytCPf5BxdxAlYbiw2o6trv1V\
a+3AIt0HZpIQEFi9kXBuCZlP5JCR7iMyMjqt3R0DuKXMohVjv+Wdfh0vRCnPgTtlKKZ8cqRc\
AsdxseXcvkvnKsdxp9XNCKC1tj9oaHId7Y4TLGhOJneyDOVoV9tzAKCgIG3wPcC/ENv56H//\
Ng2EWMcCswAAAABJRU5ErkJggg==\
"""

ICONS["fileopen.png"] = """\
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\
QRt4t1DIAAAAAElFTkSuQmCC\
"""

ICONS["filequit.png"] = """\
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\
f/+e/xfF1j2asPNr6AAAAABJRU5ErkJggg==\
"""

ICONS["filesaveall.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABmJLR0QA/wD/AP+gvaeTAAAA\
CXBIWXMAAAsSAAALEgHS3X78AAAAB3RJTUUH0woaFjotVbc2tQAAAB10RVh0Q29tbWVudABD\
cmVhdGVkIHdpdGggVGhlIEdJTVDvZCVuAAAEiUlEQVR42r2Wz2sdVRTHv5O8JI+XXy+mqQ1p\
k6UoakDtSkGo1WVF0P/AtbgQl0I34qIi7rR/gF01bkRBMBKsqwptCNiKKVQamuYZ25f3Y97M\
PT+ui3vf/MpMIYXmwuXeuXNnzvee8zlnJsBj2tW13ywRg4wgCABmATODKB3zcwZzdsyvEQla\
+wd49LCLzZuXAwCoVRlfW7tm33jzZTArRBWnT80BALb+2snte+m50zhK+2ljC2wIX30xbX9d\
/zKoFEDMiGJCP4zBkgo4++5FLC40Ua+PoT4xhhs/XDySgO1/WhARnHv7Ndz6831bLYAEIgpi\
Nw7bZGMCr7y4grmZBpqzDRy1sX+fMQa12kh1CJgFLOo6S7I+PlbD4skmmjMNNGeeTACLot3u\
QFXxGA8wRNV5QlMPnFqYxeLJWS9g8sgCiAWdgy4GYQRVi+Bp037zxrc5AZ9+/h3Cbh+dvX38\
/OMfqD1t2s+99QnWf7kEVUWr1Uav0wMxgwy5EBwH7YuLH+Drbz5Gvx/BGAYzwxiCtRa146J9\
/fctF0ZiEDMMEVQtasdFu4mdYfadKPHA8dBuiJxh9rAadgKYBcIKlnwI3nvnVaw+v4ypxgSm\
JutHFtBudxB2+4h9rJ+dnwEx4+5OC0wuBM4DzGCRxGXD9tlHF/AkrYr2C+fPgllw6fL3Pl19\
FjAJRCyIFSKKv+/uQdVCrYX1o6rCWvh1hbU22aNqk2siwv6/7VLai7WDiTNZoA5AUcWt7d3c\
tXhAs6ObO+Es7qXdTh/9Xj8tYAXacwLEiUtDwOLD4IpRlSEpCIkNod8LEfZDb8BV0zLab99+\
gJWVZ0BMEHZ7HITeAy4EUnpizoiJY4M4NhiEEeKYUsPEYEqNF2lfWJhK9kjeA5LUABHF/NwU\
VBWiNhlNTIgig8EgwlgwhonRAI2xUWeEJBNbb7SE9l5vgOnpCTBT8q1J64A/HbPi/OsvJESL\
KMIwRhwb/5Db48RKZk0O3S/S3u1GqNdH/Vc2I2B48mIhimNCGEa5lw67iPgfFim9X0b7iROT\
Dk5hqAiEM1nAmThba30aUemL80Kq7xdp395uYWlpFsKOAREGkA2Bf7DXG+D69XsuI0QSMPNj\
arzsXhnt8/MN7xVKQp5AOPwahv0IUURYXp4txFkLMddDDGQPUUb7yEjgQyBQHoZgFDUmBoti\
MIgRDiIwM9rtMHPCvMGq6+FcREppv3//HkQE/dYDqFpwHMPahvMAMaPXC5PfqXZ7kHNr1tXZ\
0OTX03kZ7VeuXIO1QOfhCADA2gZENoIakbiiYgyYBMYwzpyZKU2tYiZUQVlG+87O1aDs41Uj\
Q4ii2P0w+GKyubkLEYFq1rVa8ErqCdX8WhntVa0WGwKRuLQjJ2JpafpQjmdPnAUu6/60Rhym\
vVKAI5Z93jsGxsdHwGwRBMMeIAhG/EncGhAACBAEQTK31vUy2isFmIFB779H6Oy2QMy4c2f7\
UI4zawlsWloPhmEo0l7VAgBYXf3QHhz0YAyj2Wwkv2bWWt+RuDF/nc6La3t7+34/ILIRVAn4\
H3oJzBj8WcbGAAAAAElFTkSuQmCC\
"""

ICONS["filesaveas.png"] = """\
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\
uuUpCPAAAAAASUVORK5CYII=\
"""

ICONS["filesave.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABGdBTUEAAK/INwWK6QAAABl0\
RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAATWSURBVHjaYvz//z/DQAKAAGJi\
GGAAEEAD7gCAAGJBF1i3/sj/37//MPz+9ZeBkZGB4c+fv0AM5P9G0KjsP2A1CBpVDMR/9eYj\
w/t3nxkunJ/JiG4fQAChOGD9+qP/be31gZr/Mfz9949BRkIQLH755hMUTbrqMiT5cvvBywx/\
fv1mcHIu+b9vbw+KIwACCMUBv4G++vHzN8PXbz8Z/vxFOMDUv5FBUlSAgYODlYGDnZXh/JZG\
khxw5+Erhr9//zI4uZowSEqG/n/+fDXcEQABhOoAYHD9BVr8+w+EhgFuLnYGIx15BkE+LgYB\
fi6S4/kP1Lxfv34xsLCgJjuAAGJBVwjyORgD2TDAxsrCICkmwCAAcgAfeQ4AmfnhwyeGf//+\
ocgBBBBaCPwBxz04JJAUSojyAx3AD3UAN8kOAIXop4+fGb5/+wF0AGq5AxBAGCHw9w8oBFCj\
INDNmEFfU46BBxgVPNwcJDsA5PNvn78y/AQmRPSCDyCAMBIhyHJYkMFAXZ4fWXkcFNyvXn1g\
+PLpC9js30AHoEcBQAChhgA4Ef4HKv4HDoHbD16Cg+wf0NX/oTTIAJAnIOL/wD76B5f7D+f/\
/v2b4c3rDwxfv/4AJr4/4HLjF5YQAAggzFzwD5IAQfT1O89R+H+hCRSZhrAhDgfRoHT0+dNX\
hq9fviIKMFCBBHLA798YaQAggDCjABz8f+GFES6L/qI5BBS/X798Y/j29Ru0JISUphAzofzf\
mCEAEECYUQDKBeAo+IvVx3+QHPPz5y8wBqXun8ACDG4xiP6NsBzmsd/AqEB3AEAAsaBnF1gZ\
ALJEWJAHHOd///2H07+AFv34AbT0+w8GVkZWBnZmRgYuVmaIJb//ItULUEuB9IMnr8DR8AtL\
CAAEEGY5APUdKApcrLXgciDxb8AiGuRjSAUFUQNx7F8ksb8Y8j2z1kMdhpkLAAKIBVuRiV4Q\
gYL3GzCYkQ2F4b9//0KL8L9Y5ZFrSlAooIcAQABh5II/SPEMUgzJRr+xGozqENzyYAf8hUQL\
ugMAAgh7FEA1fvnyneH06ceQHPH3LzxhotIIy7HJycsLAdPBb2AJC0kP6A4ACCCMRAirDb8B\
ff7jx28GOTl+tHj+hxbn/zDSALInYDniL44QAAggtGz4Bxz837//ZPj2/QdYw4cP35B8iGoh\
Lj6MDcK8vOxA/m94ywrdAQABhBECoGD68uUbvDn14cN3lGBFDmrkqEEVR7A5OJihtSx2BwAE\
EEYiBBcqwIYDKNhAZbisLB/WrIWeE3AlSkjC/sPwD+RQLA4ACCBUB/wCFTI/gYXNH3hhcvHi\
c7AF//4hB+0/tFBBhAS4wEISk5bmBydAUBoAYQYGVAcABBCKA0Dl+W+wz39DKhAglpbmxcjj\
yD5GTnDIwY8oI/6A0wCsgEMPAYAAwsiG4CITnO8haYCNjQnI/g9sosMwIxAzQX0CEWNgYARj\
kByM/f8/BEOiABgyf2BRwIziAIAAQnHAr++/GL68fc/w6fkrcGK8e/cORh7/8+cflsT2D2t5\
AIuGr69egKvhPz9/Ah2A2qYECCBG9CAxMEj9//HjF3ACFBDggjfNQOogmAEejKh8BBtd7OXL\
N1D1oOL+AEq/ACCAGAe6cwoQQAPeNwQIoAF3AECAAQCAcO8MtwKEUgAAAABJRU5ErkJggg==\
"""

ICONS["helphelp.png"] = """\
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\
f5KTsrpteUOGAAAAAElFTkSuQmCC\
"""

PIXMAPS["icon.png"] = ICONS["icon.png"] = """\
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\
"""

ICONS["window.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABGdBTUEAAK/INwWK6QAAABl0\
RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAMLSURBVHjaYvz//z/DQAKAAGIE\
ERaTHhr+//dX8O/PH0z//v5l+Pf3H8O/PyAMZSPzQfQ/CP0XLP+f4T9I7O9fFD1/wfz/YHGw\
PFzN7w//zqefB1r7D4j/AwQQo8XkR4mMTMzzRPnZgAYCNf7+D6Gh+M9vGBsoDmT/AauBioH5\
/+FsFPVAc/7ALf7H8P8fkP79h+Hfz1cM/3++yme4UjgH6IAfAAHEArLcVE2AQUaYi+H3bwYw\
/vULFf9EZv9Eo0HiPyF8OBtI/waGLdANDP9AYcwKDW+gIxi/n2D4z/Z/IpC3CYhfAAQQE0gc\
bvkfiAP+AGlgSMLxXyQMNIMB6CEwDcZQsX//Uen/IIyevJiYGBj/i8B4IAYHQACxgFggn4As\
BTkAmf77B9VyuCP+QhyB4qC/mA4ikL7ZgJgZIIDADrCWRPIBzNC/CIP/4sHoIfQH5nhg4gTx\
YbkMQv1n+PmGi6FrGcIVAAHEAhRjcJCjXrYCWfgf7Jn/UPZ/KBsi9+kjJ4oDAAKIiZrlADbL\
/0OjAtkxyAAggKjmAFyWo/JBDviHog8ggJj+//tPR8sZMBwAEEBMDBSGAO5gx7QcWxQABBBF\
UYDPctREyIAzCgACiOwowO5TdMsZMNSAsicyAAggskIA2WBUy/DxYaGFGgIAAURyCKBnKeIs\
Z4BHFboDAAKIpBDAlrhIDQn0RAgQQEwMRIYAuuXIpRspIYEeAgABRFQI4LOc5JD4i+oAgABi\
+v+PVMuxpQPSHIMMAAIIbwhgt5xCx6DZARBABBxAyHLc0YIrjaADgADCmQ3xFa2UhAR6EAAE\
ENa6AF+lQklIYIsCgADCCAH8NRpllv/DEtoAAYSSBghZjt8xuIMdWR49xAECiAUUAp8/fwMX\
ELCi8j+UhvD/o8hhVfMfSRxqCdwa5GgHiv8GNRiRAEAAsYBcZ9J0C96BAPVs/qL3dJB7PMg9\
JjQ59EKGGAAQQKBuAx8QywIxP527hR+B+DFAAMH6LZxI/Rd6AWAXiOE7QAAxDnTvGCCAmBgG\
GAAEGAA4876roWF48QAAAABJRU5ErkJggg==\
"""

ICONS["docs.png"] = """\
iVBORw0KGgoAAAANSUhEUgAAABYAAAAWCAYAAADEtGw7AAAABHNCSVQICAgIfAhkiAAAABl0R\
Vh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAATQSURBVBiVtZVZTJRXFMd/dzYGhh\
kYhmVYhhE6ArIoFrFiBhIVN9RWMGpjH1qrTfvkQ5M2mj61j61tTPrQpGqXdBESK4oKaKEaLNr\
iXlRcMFjBJQwOfDAzzHzwcftQSzVYax96Xv4P95zfPefek3OElJL/w3TP6rhRiLlbXa7dtTU1\
nS8bjR+uFsLzNH/xtIw3CpFrdTheX7FmzZuleXlxdkVBjI4yYTDQJwRt58/f29/Y+LkGu+ql7\
HsqeKMQaXqT6ZWqDRveListdTrHxxGhEKgqjI1NUc1m43edjp/OnetpbGn5zAhf1En54DHwq0\
JsWb1mzY5VVVXC8ATIE/URG4mJ4ZsDB8Y/7unxGh49mO5wbKoCcb62llBCAqnZ2eQkJoIQD+u\
bqpqU3PH7CdtsRHu9aL29gXs9PdbHwGmZmVlRGS5KFQUUhZGuq5wcGUFLTCTT7cYdZQIhmJCS\
fkVhUAiSFi4kvboavc0GgG7//vAodE2CRcninHcGh0fJm2ElEABFwTo8xPyHl/iudtEWDKKzW\
vFUVpK4bRvOpKQpHy5V1ZIKeoMoWVxQXr6s+d33d2b4vviEK0eayMsvQBcfDy4XKEOgKCQpCh\
afj751a3HW1EwBTgSD+A8exHDmTKweSgwCw1s31KKMO82/4ppdxXt3unAcbmCB9oCygnyyp+d\
CvB0yXNw83UHu8uV/w8JhlKYmLtfW0nLoUOh0KHS4Gxr64KQhOiXPa3PPQQur3AqNcg2wlqdz\
1Wbiy5udZP3QxFJTmLKiQnJdLm7s3UuGw0F3bS3tLS0MFxdzyWIfqwuF1gPHpJRBAMN40NdrT\
rIXT6hjaGGVqLg4tIhKbzBAxKbn9qIcOqNMpF9vZ+blY8R99y2BrCzcK1dSuXUrLpeLD3Z9L2\
movyojoeBf1RhU5W7HcPflVdFJbvRmE6a4WLRwBFPYgtluR4uoFNjOs3v7dgBUVUXTNMxmM0I\
I/AGN64Mpptj8nH2isHCLvHTpOICg0Jsg0H9kTn1+vTXTa7FNm4cx1obebEJnMhIZ8rHDO8Cy\
ufmTbxsIT3Cgw8+eltO0ndlLcvIFisrN9PQlcHHXhc2yt3e3QXae8AOb7Mu99kUvhapP7fuaf\
n8+MaleYjPnYIg280v3IAtmSxrPKexp/Y2j7fuxx7eTmT9BWU06nrRq1udX0dhwInKx/2g/wG\
Qfp2TGZ1eueIGyxUFGIsOcPVrPqfqdBEPF1CY4+bTuCPa4k2QVRqhY6yAlYQnVs5ayxDUPg+5\
PTCMnJKra9Ri458r9M/eG7s6yxthwWp0srU7CuyLIYHCIW53n6Lt+H0LJvPHia6yaVkG0wTyl\
l8fEuJHkZDfQPQlWg2MtDV91bCqpmkZyih2LMRaLyYIn6Tmc3hRG5oyg/zmZdZ4lU4C9gfvUX\
fmR+lvHBVLmAK2PTTcxffpsEW3cnFbqqMktT3UWlWeSmBiPxRiLFtBR4itjQUEpAP2jfvZeb2\
VPazPtzadvy5vBZgYG6hkePiul9P3joBcez3y9JWqja37y6lxvauLMCjdah52iGXnsaTtCa+O\
pfu2a0sLA0D78/g6gX0oZmYz/t50nhBB4PBUGa9QmU7ppbuhm8AoDgw34fMeB+1LK8BPj/usy\
FUII+QxBfwBZwhv1Cgi1ZAAAAABJRU5ErkJggg==\
"""

def getIcon(name):
    icon = ICONS.get(name)
    if icon is None:
        return QIcon()
    if isinstance(icon, basestring):
        pixmap = QPixmap()
        pixmap.loadFromData(base64.b64decode(icon))
        icon = QIcon(pixmap)
        ICONS[name] = icon
    return icon


def getPixmap(name):
    image = PIXMAPS.get(name)
    if image is None:
        return QPixmap()
    if isinstance(image, basestring):
        pixmap = QPixmap()
        pixmap.loadFromData(base64.b64decode(image))
        PIXMAPS[name] = image = pixmap
    return image


def isAlive(qobj):
    import sip
    try:
        sip.unwrapinstance(qobj)
    except RuntimeError:
        return False
    return True


def main():
    if not hasattr(sys, "ps1"):
        sys.ps1 = ">>> "
    if not hasattr(sys, "ps2"):
        sys.ps2 = "... "
    app = QApplication(sys.argv)
    if not sys.platform.startswith(("linux", "win")):
        app.setCursorFlashTime(0)
    app.setOrganizationName("Qtrac Ltd.")
    app.setOrganizationDomain("qtrac.eu")
    app.setApplicationName("Sandbox")
    app.setWindowIcon(getIcon("icon.png"))
    loadConfig()

    for name in KEYWORDS + BUILTINS + CONSTANTS:
        if len(name) >= MIN_COMPLETION_LEN and not name.startswith("_"):
            CAT[name] = ""
            try:
                tip = eval("%s.__doc__" % name)
                if tip is not None:
                    CAT[name] = (tip[:MAX_TOOLTIP_LEN]
                                 .strip().replace("\n\n", "<p>"))
            except:
                pass
    for name in MODULES.keys():
        CAT[name] = None

    if len(sys.argv) > 1:
        args = sys.argv[1:]
        if args[0] in ("-h", "--help"):
            args.pop(0)
            print """usage: sandbox.pyw [-n|filenames]
-n or --new means start with new file
filenames   means start with the given files (which must have .py or .pyw
            suffixes); otherwise starts with new file or Python shell
            depending on configuration
Sandbox requires Python 2.5 and PyQt 4.2 (or later versions)
For more information run the program and click
Help->About and Help->Help"""
            return
        if args and args[0] in ("-n", "--new"):
            args.pop(0)
            MainWindow().show()
        dir = QDir()
        for fname in args:
            if fname.endswith((".py", ".pyw")):
                MainWindow(dir.cleanPath(
                        dir.absoluteFilePath((fname)))).show()
    if not MainWindow.Instances:
        MainWindow(isShell=Config["startwithshell"]).show()

    app.exec_()
    saveConfig()


main()

### Ideas for improvements ##############################################
#
# - Make Indent & Unindent smarter, i.e., Indent should insert _up to_
#   tabwidth spaces to make the number of leading spaces an exact multiple
#   of tabwidth. Similarly, Unindent should remove _up to_ tabwidth
#   spaces on the same basis
# - Recent files handling
# - Add tooltips to all ConfigForm editing widgets & improve validation
# - Add tooltips to all main window actions that don't have any.
# - Goto menu. Use submenus to reflect the structure of the code, i.e.,
#   classes
#      Class1
#        Method1
#        Method2
#   functions
#       Func1
#       Func2
#          InnerFuncA
#   This should be doable when reading, but trickier to maintain when 
#   users add or change classes and defs since the right "parent" must be
#   found, and the name put in the right place in the tree
# - Robustness? catch exceptions better, etc.
# - Help? Handle help() in the shell?
# - Tools menu? (modeless delete on close dialogs); e.g.,
#   Regular Expression Editor (similar to the one I wrote as an
#   example for TT); support multiple syntaxes, e.g., re, glob,
#   (fnmatch?), QRegExp, and QRegExp wildcard
# - i18n? use a custom dictionary-like function and keep all
#   translations in this same file; or embed .qm files in base64?
# - Autosave? If not zero auto saves every N seconds to
#   .sb$.self.filename. On close the .sb$. file is deleted after the
#   save. On open, if a .sb$. file exists, rename it self.filename#1 (or
#   2 or whatever to make it unique) and then give a warning to the user
#   that they may wish to diff against it. So we don't do recover as
#   such.
# - Make keyboard shortcuts customisable? (apart from the standard ones)
