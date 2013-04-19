# This script generates the PyQt configuration and generates the Makefiles.
#
# Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
# 
# This file is part of PyQt.
# 
# This file may be used under the terms of the GNU General Public
# License versions 2.0 or 3.0 as published by the Free Software
# Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
# included in the packaging of this file.  Alternatively you may (at
# your option) use any later version of the GNU General Public
# License if such license has been publicly approved by Riverbank
# Computing Limited (or its successors, if any) and the KDE Free Qt
# Foundation. In addition, as a special exception, Riverbank gives you
# certain additional rights. These rights are described in the Riverbank
# GPL Exception version 1.1, which can be found in the file
# GPL_EXCEPTION.txt in this package.
# 
# Please review the following information to ensure GNU General
# Public Licensing requirements will be met:
# http://trolltech.com/products/qt/licenses/licensing/opensource/. If
# you are unsure which license is appropriate for your use, please
# review the following information:
# http://trolltech.com/products/qt/licenses/licensing/licensingoverview
# or contact the sales department at sales@riverbankcomputing.com.
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


import sys
import os
import glob
import optparse
import shutil

import sipconfig


# Initialise the globals.
pyqt_version = 0x040800
pyqt_version_str = "4.8"

sip_min_version = 0x040b02

qt_version = 0
qt_edition = ""
qt_licensee = None
qt_dir = None
qt_incdir = None
qt_libdir = None
qt_bindir = None
qt_datadir = None
qt_pluginsdir = None
qt_xfeatures = None
qt_shared = ""
qt_framework = 0

qt_sip_flags = []

pyqt_modules = []
pyqt_modroot = None
src_dir = os.path.dirname(os.path.abspath(__file__))

# Get the SIP configuration.
sipcfg = sipconfig.Configuration()

pydbusmoddir = None
dbusincdirs = []
dbuslibdirs = []
dbuslibs = []


# Under Windows qmake and the Qt DLLs must be into the system PATH otherwise
# the dynamic linker won't be able to resolve the symbols.  On other systems we
# assume we can just run qmake by using its full pathname.
if sys.platform == 'win32':
    MSG_CHECK_QMAKE = "Make sure you have a working Qt v4 qmake on your PATH."
else:
    MSG_CHECK_QMAKE = "Make sure you have a working Qt v4 qmake on your PATH or use the -q argument to explicitly specify a working Qt v4 qmake."


def find_default_qmake():
    """Find a default qmake, ie. the first on the path.
    """
    try:
        path = os.environ["PATH"]
    except KeyError:
        path = ""

    if sys.platform == 'win32':
        base_qmake = "qmake.exe"
    else:
        base_qmake = "qmake"

    for d in path.split(os.pathsep):
        qmake = os.path.join(d, base_qmake)
  
        if os.access(qmake, os.X_OK):
            return qmake

    return ""


def create_optparser():
    """Create the parser for the command line.
    """
    qmake = find_default_qmake()

    def store_abspath(option, opt_str, value, parser):
        setattr(parser.values, option.dest, os.path.abspath(value))

    def store_abspath_dir(option, opt_str, value, parser):
        if not os.path.isdir(value):
            raise optparse.OptionValueError("'%s' is not a directory" % value)
        setattr(parser.values, option.dest, os.path.abspath(value))
        
    def store_abspath_file(option, opt_str, value, parser):
        if not os.path.isfile(value):
            raise optparse.OptionValueError("'%s' is not a file" % value)
        setattr(parser.values, option.dest, os.path.abspath(value))

    p = optparse.OptionParser(usage="python %prog [opts] [macro=value] "
            "[macro+=value]", version=pyqt_version_str)

    # Note: we don't use %default to be compatible with Python 2.3.
    p.add_option("-k", "--static", action="store_true", default=False,
            dest="static", help="build modules as static libraries")
    p.add_option("--no-docstrings", action="store_true", default=False,
            dest="no_docstrings", help="disable the generation of docstrings")
    p.add_option("-r", "--trace", action="store_true", default=False,
            dest="tracing", help="build modules with tracing enabled")
    p.add_option("-u", "--debug", action="store_true", default=False,
            help="build modules with debugging symbols")
    p.add_option("-w", "--verbose", action="count", default=0, dest="verbose",
            help="verbose output during configuration")

    p.add_option("-c", "--concatenate", action="store_true", default=False,
            dest="concat", help="concatenate each module's C++ source files")
    p.add_option("-j", "--concatenate-split", type="int", default=1,
            metavar="N", dest="split",
            help="split the concatenated C++ source files into N pieces "
            "[default: 1]")
    p.add_option("-g", "--consolidate", action="store_true", default=False,
            dest="bigqt", help="create a single module which links against "
            "all the Qt libraries")

    # These are internal options used to build the mega Windows GPL package.
    p.add_option("--mwg-odbc", action="store_true", default=False,
            dest="mwg_odbc", help=optparse.SUPPRESS_HELP)
    p.add_option("--mwg-openssl", action="callback", default=None,
            dest="mwg_ssl_dir", metavar="DIR", callback=store_abspath_dir,
            type="string", help=optparse.SUPPRESS_HELP)
    p.add_option("--mwg-qsci", action="callback", default=None,
            dest="mwg_qsci_dir", metavar="DIR", callback=store_abspath_dir,
            type="string", help=optparse.SUPPRESS_HELP)
    p.add_option("--mwg-qwt", action="callback", default=None,
            dest="mwg_qwt_dir", metavar="DIR", callback=store_abspath_dir,
            type="string", help=optparse.SUPPRESS_HELP)

    # Configuration.
    g = optparse.OptionGroup(p, title="Configuration")
    g.add_option("--confirm-license", action="store_true", default=False,
            dest="license_confirmed", help="confirm acceptance of the license")
    g.add_option("-e", "--enable", action="append", default=[],
            metavar="MODULE", dest="enabled", help="enable checks for the "
            "specified MODULE [default: checks for all modules will be "
            "enabled]")
    g.add_option("--no-designer-plugin", action="store_false", default=True,
            dest="designer_plugin", help="disable the building of the "
            "Python plugin for Qt Designer [default: enabled]")
    g.add_option("-t", "--plugin", action="append", default=[],
            metavar="PLUGIN", dest="staticplugins", help="add PLUGIN to the "
            "list be linked (if Qt is built as static libraries)")
    g.add_option("--assume-shared", action="store_true", default=False,
            dest="assume_shared", help="assume that the Qt libraries have "
            "been built as shared libraries [default: check]")

    if sys.platform != 'win32':
        if sys.platform in ('linux2', 'darwin'):
            pip_default = True
            pip_default_str = "enabled"
        else:
            pip_default = False
            pip_default_str = "disabled"

        g.add_option("--protected-is-public", action="store_true",
                default=pip_default, dest="prot_is_public",
                help="enable building with 'protected' redefined as 'public' "
                        "[default: %s]" % pip_default_str)
        g.add_option("--protected-not-public", action="store_false",
                dest="prot_is_public",
                help="disable building with 'protected' redefined as 'public'")
        g.add_option("-q", "--qmake", action="callback", metavar="FILE",
                default=qmake, dest="qmake", callback=store_abspath_file,
                type="string",
                help="the pathname of qmake [default: %s]" % (qmake or "none"))

    g.add_option("-s", "--dbus", action="callback", metavar="DIR",
            dest="pydbusincdir", callback=store_abspath_dir, type="string",
            help="the directory containing the dbus/dbus-python.h header file "
            "[default: supplied by pkg-config]")
    p.add_option_group(g)

    if sys.platform == 'darwin':
        g = optparse.OptionGroup(p, title="MacOS X Configuration")
        g.add_option("--use-arch", action="store", metavar="ARCH",
                dest="use_arch", choices=["i386", "x86_64", "ppc"],
                help="the architecture to use when running pyuic4 "
                        "[default: system default]")
        p.add_option_group(g)

    # Installation.
    g = optparse.OptionGroup(p, title="Installation")
    g.add_option("-b", "--bindir", action="callback",
            default=sipcfg.default_bin_dir, type="string", metavar="DIR",
            dest="pyqtbindir", callback=store_abspath, help="where pyuic4, "
            "pyrcc4 and pylupdate4 will be installed [default: %s]" %
            sipcfg.default_bin_dir)
    g.add_option("-d", "--destdir", action="callback",
            default=sipcfg.default_mod_dir, type="string", metavar="DIR",
            dest="pyqtmoddir", callback=store_abspath, help="where the PyQt4 "
            "Python package will be installed [default: %s]" %
            sipcfg.default_mod_dir)
    g.add_option("-p", "--plugin-destdir", action="callback", type="string",
            metavar="DIR", dest="plugindir", callback=store_abspath,
            help="where any plugins will be installed [default: "
            "QTDIR/plugins]")
    g.add_option("--no-sip-files", action="store_false", default=True,
            dest="install_sipfiles", help="disable the installation of the "
            ".sip files [default: enabled]")
    g.add_option("-v", "--sipdir", action="callback",
            default=os.path.join(sipcfg.default_sip_dir, "PyQt4"),
            metavar="DIR", dest="pyqtsipdir", callback=store_abspath,
            type="string", help="where the PyQt4 .sip files will be installed "
            "[default: %s]" % sipcfg.default_sip_dir)
    p.add_option_group(g)

    # Vendor ID.
    g = optparse.OptionGroup(p, title="VendorID support")
    g.add_option("-i", "--vendorid", action="store_true", default=False,
            dest="vendorcheck", help="enable checking of signed interpreters "
            "using the VendorID package [default: disabled]")
    g.add_option("-l", "--vendorid-incdir", action="callback",
            default=sipcfg.py_inc_dir, type="string", metavar="DIR",
            dest="vendincdir", callback=store_abspath_dir, help="the "
            "directory containing the VendorID header file [default: %s]" %
            sipcfg.py_inc_dir)
    g.add_option("-m", "--vendorid-libdir", action="callback",
            default=sipcfg.py_lib_dir, type="string", metavar="DIR",
            dest="vendlibdir", callback=store_abspath_dir, help="the "
            "directory containing the VendorID library [default: %s]" %
            sipcfg.py_lib_dir)
    p.add_option_group(g)

    # QScintilla.
    g = optparse.OptionGroup(p, title="QScintilla support")
    g.add_option("-a", "--qsci-api", action="store_true", default=None,
            dest="api", help="always install the PyQt API file for QScintilla "
            "[default: install only if QScintilla installed]")
    g.add_option("--no-qsci-api", action="store_false", default=None,
            dest="api", help="do not install the PyQt API file for QScintilla "
            "[default: install only if QScintilla installed]")
    g.add_option("-n", "--qsci-api-destdir", action="callback", dest="qscidir",
            metavar="DIR", callback=store_abspath, type="string", help="where "
            "the PyQt API file for QScintilla will be installed [default: "
            "QTDIR/qsci]")
    p.add_option_group(g)

    return p


class pyrccMakefile(sipconfig.ProgramMakefile):
    """This class implements the Makefile for pyrcc.  This is specialised so
    that pyrcc is automatically run against the examples.
    """

    def __init__(self):
        sipconfig.ProgramMakefile.__init__(self, configuration=sipcfg,
                build_file=os.path.join(src_dir, "pyrcc", "pyrcc.sbf"),
                dir="pyrcc", install_dir=opts.pyqtbindir, console=1,
                qt=["QtCore", "QtXml"], debug=opts.debug, warnings=1,
                universal=sipcfg.universal, arch=sipcfg.arch)

    def generate_target_default(self, mfile):
        """Generate the default target."""
        sipconfig.ProgramMakefile.generate_target_default(self, mfile)

        # The correct call to pyrcc depends on the Python version.
        if sys.hexversion >= 0x03000000:
            flag = "-py3"
        else:
            flag = "-py2"

        exe = "$(TARGET)"
        if sys.platform != 'win32':
            exe = "./" + exe

        # Find all the .qrc files in the examples.
        for root, _, files in os.walk("examples"):
            rel_root = os.path.join("..", root)

            for fn in files:
                if fn.endswith(".qrc"):
                    mfile.write("\t%s %s -o %s %s\n" % (exe, flag, os.path.join(rel_root, fn[:-4] + "_rc.py"), os.path.join(rel_root, fn)))


class ConfigurePyQt4:
    """This class defines the methods to configure PyQt4.
    """
    def __init__(self, generator):
        self.generator = generator

    def qt_version_tags(self):
        """Get the versions tags for the configuration.

        Returns a dictionary of versions and corresponding tags.
        """
        return {
            0x040101: None,
            0x040102: "Qt_4_1_1",
            0x040103: "Qt_4_1_2",
            0x040200: "Qt_4_1_3",
            0x040202: "Qt_4_2_0",
            0x040300: "Qt_4_2_2",
            0x040303: "Qt_4_3_0",
            0x040400: "Qt_4_3_3",
            0x040401: "Qt_4_4_0",
            0x040500: "Qt_4_4_1",
            0x040501: "Qt_4_5_0",
            0x040600: "Qt_4_5_1",
            0x040601: "Qt_4_6_0",
            0x040602: "Qt_4_6_1",
            0x040603: "Qt_4_6_2",
            0x040700: "Qt_4_6_3",
            0x050000: "Qt_4_7_0"
        }

    def check_modules(self):
        if opts.mwg_odbc:
            sql_libs = ["odbc32"]
        else:
            sql_libs = None

        if opts.mwg_ssl_dir:
            ass_lib_dirs = [os.path.join(opts.mwg_ssl_dir, "lib")]
            ass_libs = ["ssleay32", "libeay32"]
        else:
            ass_lib_dirs = None
            ass_libs = None

        # Note that the order in which we check is important for the
        # consolidated module - a module's dependencies must be checked first.
        pyqt_modules.append("QtCore")

        check_module("QtGui", "qwidget.h", "new QWidget()")
        check_module("QtHelp", "qhelpengine.h", "new QHelpEngine(\"foo\")")
        check_module("QtMultimedia", "QAudioDeviceInfo",
                "new QAudioDeviceInfo()")
        check_module("QtNetwork", "qhostaddress.h", "new QHostAddress()")
        check_module("QtDeclarative", "qdeclarativeview.h",
                "new QDeclarativeView()")
        check_module("QtOpenGL", "qgl.h", "new QGLWidget()")
        check_module("QtScript", "qscriptengine.h", "new QScriptEngine()")
        check_module("QtScriptTools", "qscriptenginedebugger.h",
                "new QScriptEngineDebugger()")
        check_module("QtSql", "qsqldatabase.h", "new QSqlDatabase()",
                extra_libs=sql_libs)
        check_module("QtSvg", "qsvgwidget.h", "new QSvgWidget()")
        check_module("QtTest", "QtTest", "QTest::qSleep(0)")
        check_module("QtWebKit", "qwebpage.h", "new QWebPage()")
        check_module("QtXml", "qdom.h", "new QDomDocument()")
        check_module("QtXmlPatterns", "qxmlname.h", "new QXmlName()")
        check_module("phonon", "phonon/videowidget.h",
                "new Phonon::VideoWidget()")
        check_module("QtAssistant", "qassistantclient.h",
                "new QAssistantClient(\"foo\")", extra_lib_dirs=ass_lib_dirs,
                extra_libs=ass_libs)

        if not qt_shared:
            sipconfig.inform("QtDesigner module disabled with static Qt libraries.")
        elif sipcfg.universal:
            sipconfig.inform("QtDesigner module disabled with universal binaries.")
        else:
            check_module("QtDesigner", "QExtensionFactory",
                    "new QExtensionFactory()")

        check_module("QAxContainer", "qaxobject.h", "new QAxObject()",
                extra_libs=["QAxContainer"])

        if os.path.isdir(os.path.join(src_dir, "dbus")):
            check_dbus()

    def code(self):
        cons_xtra_incdirs = []
        cons_xtra_libdirs = []
        cons_xtra_libs = []

        sp_libs, sp_libdirs = self._static_plugins("QtCore")
        sp_incdirs = []

        qpy_inc_dir, qpy_lib_dir, qpy_lib = self._qpy_directories("QtCore", "qpycore")
        sp_incdirs.append(qpy_inc_dir)
        sp_libdirs.append(qpy_lib_dir)
        sp_libs.append(qpy_lib)

        if opts.vendorcheck:
            sp_incdirs.append(opts.vendincdir)
            sp_libdirs.append(opts.vendlibdir)
            sp_libs.append("vendorid")

        if opts.bigqt:
            cons_xtra_incdirs.extend(sp_incdirs)
            cons_xtra_libdirs.extend(sp_libdirs)
            cons_xtra_libs.extend(sp_libs)

            generate_code("QtCore")
        else:
            generate_code("QtCore", extra_include_dirs=sp_incdirs,
                        extra_lib_dirs=sp_libdirs, extra_libs=sp_libs)

        if "QtDeclarative" in pyqt_modules:
            qpy_inc_dir, qpy_lib_dir, qpy_lib = self._qpy_directories("QtDeclarative", "qpydeclarative")

            if opts.bigqt:
                cons_xtra_incdirs.append(qpy_inc_dir)
                cons_xtra_libdirs.append(qpy_lib_dir)
                cons_xtra_libs.append(qpy_lib)

                generate_code("QtDeclarative")
            else:
                generate_code("QtDeclarative", extra_include_dirs=[qpy_inc_dir],
                        extra_lib_dirs=[qpy_lib_dir], extra_libs=[qpy_lib])

        if "QtGui" in pyqt_modules:
            sp_libs, sp_libdirs = self._static_plugins("QtGui")
            sp_incdirs = []

            qpy_inc_dir, qpy_lib_dir, qpy_lib = self._qpy_directories("QtGui", "qpygui")
            sp_incdirs.append(qpy_inc_dir)
            sp_libdirs.append(qpy_lib_dir)
            sp_libs.append(qpy_lib)

            if opts.bigqt:
                cons_xtra_incdirs.extend(sp_incdirs)
                cons_xtra_libdirs.extend(sp_libdirs)
                cons_xtra_libs.extend(sp_libs)

                generate_code("QtGui")
            else:
                generate_code("QtGui", extra_include_dirs=sp_incdirs,
                        extra_lib_dirs=sp_libdirs, extra_libs=sp_libs)

        if "QtHelp" in pyqt_modules:
            generate_code("QtHelp")

        if "QtMultimedia" in pyqt_modules:
            generate_code("QtMultimedia")

        if "QtNetwork" in pyqt_modules:
            generate_code("QtNetwork")

        if "QtOpenGL" in pyqt_modules:
            generate_OpenGL_extras()
            generate_code("QtOpenGL")

        if "QtScript" in pyqt_modules:
            generate_code("QtScript")

        if "QtScriptTools" in pyqt_modules:
            generate_code("QtScriptTools")

        if "QtSql" in pyqt_modules:
            sp_libs, sp_libdirs = self._static_plugins("QtSql")

            if opts.bigqt:
                cons_xtra_libdirs.extend(sp_libdirs)
                cons_xtra_libs.extend(sp_libs)

                generate_code("QtSql")
            else:
                generate_code("QtSql", extra_lib_dirs=sp_libdirs,
                        extra_libs=sp_libs)

        if "QtSvg" in pyqt_modules:
            generate_code("QtSvg")

        if "QtTest" in pyqt_modules:
            generate_code("QtTest")

        if "QtWebKit" in pyqt_modules:
            generate_code("QtWebKit")

        if "QtXml" in pyqt_modules:
            generate_code("QtXml")

        if "QtXmlPatterns" in pyqt_modules:
            generate_code("QtXmlPatterns")

        if "phonon" in pyqt_modules:
            generate_code("phonon")

        if "QtAssistant" in pyqt_modules:
            generate_code("QtAssistant")

        if "QtDesigner" in pyqt_modules:
            qpy_inc_dir, qpy_lib_dir, qpy_lib = self._qpy_directories("QtDesigner", "qpydesigner")

            if opts.bigqt:
                cons_xtra_incdirs.append(qpy_inc_dir)
                cons_xtra_libdirs.append(qpy_lib_dir)
                cons_xtra_libs.append(qpy_lib)

                generate_code("QtDesigner")
            else:
                generate_code("QtDesigner", extra_include_dirs=[qpy_inc_dir],
                        extra_lib_dirs=[qpy_lib_dir], extra_libs=[qpy_lib])

        if "QAxContainer" in pyqt_modules:
            generate_code("QAxContainer")

        # Generate the composite module.
        qtmod_sipdir = os.path.join("sip", "Qt")
        mk_clean_dir(qtmod_sipdir)

        qtmod_sipfile = os.path.join(qtmod_sipdir, "Qtmod.sip")
        f = open(qtmod_sipfile, "w")

        f.write("""%CompositeModule PyQt4.Qt

""")

        for m in pyqt_modules:
            f.write("%%Include %s/%smod.sip\n" % (m, m))

        f.close()

        generate_code("Qt")

        # Generate the consolidated module if required.
        if opts.bigqt:
            xtra_sip_flags = []

            _qtmod_sipdir = os.path.join("sip", "_qt")
            mk_clean_dir(_qtmod_sipdir)

            _qtmod_sipfile = os.path.join(_qtmod_sipdir, "_qtmod.sip")
            f = open(_qtmod_sipfile, "w")

            f.write("""%ConsolidatedModule PyQt4._qt

""")

            for m in pyqt_modules:
                f.write("%%Include %s/%smod.sip\n" % (m, m))

            if opts.mwg_qsci_dir:
                f.write("%Include Qsci/Qscimod.sip\n")
                cons_xtra_libs.append("qscintilla2")

                # Copy in the QScintilla .sip files and fix the main one.
                src_dir = os.path.join(opts.mwg_qsci_dir, "Python", "sip")
                dst_dir = os.path.join("sip", "Qsci")

                try:
                    shutil.rmtree(dst_dir);
                except:
                    pass

                shutil.copytree(src_dir, dst_dir)
                os.rename(os.path.join(dst_dir, "qscimod4.sip"), os.path.join(dst_dir, "Qscimod.sip"))

                generate_code("Qsci")

            if opts.mwg_qwt_dir:
                f.write("%Include Qwt5/Qwt5mod.sip\n")
                cons_xtra_incdirs.append(os.path.join(opts.mwg_qwt_dir, "support"))
                cons_xtra_libs.append("qwt")

                # Copy in the PyQwt .sip files and fix the main one.
                src_dir = os.path.join(opts.mwg_qwt_dir, "sip", "qwt5qt4")
                dst_dir = os.path.join("sip", "Qwt5")

                try:
                    shutil.rmtree(dst_dir);
                except:
                    pass

                shutil.copytree(src_dir, dst_dir)
                os.rename(os.path.join(dst_dir, "QwtModule.sip"), os.path.join(dst_dir, "Qwt5mod.sip"))

                xtra_sip_flags = ["-t", "Qwt_5_0_1",
                                  "-x", "CXX_DYNAMIC_CAST",
                                  "-x", "HAS_QWT4",
                                  "-x", "HAS_NUMARRAY",
                                  "-x", "HAS_NUMERIC",
                                  "-x", "HAS_NUMPY"]

                generate_code("Qwt5", extra_sip_flags=xtra_sip_flags)

            f.close()

            if opts.mwg_odbc:
                cons_xtra_libs.append("odbc32")

            if opts.mwg_ssl_dir:
                cons_xtra_libdirs.append(os.path.join(opts.mwg_ssl_dir, "lib"))
                cons_xtra_libs.extend(["ssleay32", "libeay32"])

            generate_code("_qt", extra_include_dirs=cons_xtra_incdirs,
                    extra_lib_dirs=cons_xtra_libdirs,
                    extra_libs=cons_xtra_libs, extra_sip_flags=xtra_sip_flags)

        # Tell the user about any plugins not found.
        if opts.staticplugins:
            sipconfig.inform("Unable to find the following static plugins: %s" % ", ".join(opts.staticplugins))

        # Generate the QScintilla API file.
        sipconfig.inform("Creating QScintilla API file...")
        f = open("PyQt4.api", "w")

        for m in pyqt_modules:
            api = open(m + ".api")

            for l in api:
                f.write("PyQt4." + l)

            api.close()
            os.remove(m + ".api")

        f.close()

    def _qpy_directories(self, mname, lib_name):
        """Return a 3-tuple of the directories containing the header files, the
        directory containing the library, and the name of the support library
        for the given module.

        mname is the name of the module.
        lib_name is the normal name of the support library.
        """
        qpy_dir = os.path.join("qpy", mname)

        if sys.platform == 'win32':
            if opts.debug:
                qpy_lib_dir = os.path.join(qpy_dir, "debug")
                lib_name = 'd' + lib_name
            else:
                qpy_lib_dir = os.path.join(qpy_dir, "release")
        else:
            qpy_lib_dir = qpy_dir

        return os.path.join(src_dir, qpy_dir), os.path.abspath(qpy_lib_dir), lib_name

    def _static_plugins(self, mname):
        """Return a tuple of the libraries (in platform neutral format) and the
        directories they are contained in for all the requested static plugins
        for the given module.  Generate the additional .sip file needed to
        ensure the plugins get linked.

        mname is the name of the module.
        """
        plugin_dirs = {
            "QtCore":   ("codecs", ),
            # Note that we put iconengines after imageformats so that qsvg is
            # found in the latter rather than the former.  The name clash is
            # probably a Qt bug.
            "QtGui":    ("inputmethods", "imageformats", "iconengines"),
            "QtSql":    ("sqldrivers", )
        }

        libs = []
        libdirs = []

        for plug in opts.staticplugins:
            # Convert the plugin name to a platform specific filename.
            if self.generator in ("MSVC", "MSVC.NET", "BMAKE"):
                pfname = plug + ".lib"
            else:
                pfname = "lib" + plug + ".a"

            for pdir in plugin_dirs[mname]:
                ppath = os.path.join(qt_pluginsdir, pdir)

                # See if the plugin exists.
                if os.access(os.path.join(ppath, pfname), os.F_OK):
                    sipconfig.inform("Adding the %s static plugin to the %s module..." % (plug, mname))

                    libs.append(plug)

                    if ppath not in libdirs:
                        libdirs.append(ppath)

                    break

        # Remove those plugins we have handled.
        opts.staticplugins = [p for p in opts.staticplugins if p not in libs]

        # If we have any plugins for this module then generate a .sip file that
        # will include the code needed to ensure the plugin gets linked.
        if libs:
            sp_sipfile = os.path.join("sip", mname, "staticplugins.sip")

            f = open(sp_sipfile, "w")

            f.write("""%ModuleCode

#include <QtPlugin>

""")

            for l in libs:
                f.write("Q_IMPORT_PLUGIN(%s)\n" % l)

            f.write("""
%End
""")

            f.close()

        return libs, libdirs

    def module_installs(self):
        return [os.path.join(src_dir, "__init__.py"), "pyqtconfig.py"]

    def qpy_libs(self):
        # See which QPy support libraries to build.
        qpylibs = {}

        if "QtCore" in pyqt_modules:
            qpylibs["QtCore"] = "qpycore.pro"

        if "QtGui" in pyqt_modules:
            qpylibs["QtGui"] = "qpygui.pro"

        if "QtDeclarative" in pyqt_modules:
            qpylibs["QtDeclarative"] = "qpydeclarative.pro"

        if "QtDesigner" in pyqt_modules:
            qpylibs["QtDesigner"] = "qpydesigner.pro"

        # Run qmake to generate the Makefiles.
        qmake_args = fix_qmake_args()
        cwd = os.getcwd()

        for qpy, pro in qpylibs.items():
            sipconfig.inform("Creating QPy support library for %s Makefile..." % qpy)

            qpydir = os.path.join("qpy", qpy)
            mk_clean_dir(qpydir, clean=0)
            os.chdir(qpydir)

            wrapped_pro = "w_" + pro

            f = open(wrapped_pro, 'w+')

            if sipcfg.arch:
                f.write(arch_config())

            if sipcfg.universal:
                f.write("QMAKE_MAC_SDK = %s\n" % sipcfg.universal)

            inc_path = [sipcfg.py_inc_dir]
            if qpy in ("QtCore", "QtDeclarative"):
                if sipcfg.sip_inc_dir != sipcfg.py_inc_dir:
                    inc_path.insert(0, sipcfg.sip_inc_dir)

                if opts.bigqt:
                    api_dir = "../../_qt"
                else:
                    api_dir = "../../" + qpy

                inc_path.append(api_dir)

            if opts.debug:
                pro_config = 'debug'
            else:
                pro_config = 'release'

            if src_dir != os.path.curdir:
                src_qpydir = os.path.join(src_dir, "qpy", qpy)
                pro = os.path.join(src_qpydir, pro)
                vpath = "VPATH = " + src_qpydir
                inc_path.append(src_qpydir)
            else:
                vpath = ""

            f.write(
"""# Tell the original .pro file about additional directories.
INCLUDEPATH = %s
CONFIG += %s
%s
include(%s)
""" % (" ".join(['"' + i + '"' for i in inc_path]), pro_config, vpath, pro))

            f.close()

            run_command("%s %s %s" % (opts.qmake, qmake_args, wrapped_pro))
            os.chdir(cwd)

        sipconfig.inform("Creating QPy support libraries Makefile...")

        sipconfig.ParentMakefile(
            configuration=sipcfg,
            dir="qpy",
            subdirs=list(qpylibs.keys())
        ).generate()

        return ["qpy"]

    def tools(self):
        tool = []

        if pydbusmoddir:
            sipconfig.inform("Creating dbus support module Makefile...")

            makefile = sipconfig.ModuleMakefile(
                configuration=sipcfg,
                build_file=os.path.join(src_dir, "dbus", "dbus.sbf"),
                dir="dbus",
                install_dir=pydbusmoddir,
                qt=["QtCore"],
                debug=opts.debug,
                universal=sipcfg.universal,
                arch=sipcfg.arch
            )

            add_makefile_extras(makefile, dbusincdirs, dbuslibdirs, dbuslibs)

            makefile.generate()
            tool.append("dbus")

        # Only include ElementTree for older versions of Python.
        if sipcfg.py_version < 0x020500:
            sipconfig.inform("Creating elementtree Makefile...")

            makefile = sipconfig.PythonModuleMakefile(
                configuration=sipcfg,
                dstdir=os.path.join(pyqt_modroot, "elementtree"),
                dir="elementtree"
            )

            makefile.generate()
            tool.append("elementtree")

        # Create the pyuic4 wrapper.  Use the GUI version on MacOS (so that
        # previews work properly and normal console use will work anyway), but
        # not on Windows (so that normal console use will work).
        sipconfig.inform("Creating pyuic4 wrapper...")

        if sys.platform == 'darwin':
            gui = True
            use_arch = opts.use_arch
        else:
            gui = False
            use_arch = ''

        uicdir=os.path.join(pyqt_modroot, "uic")
        wrapper = sipconfig.create_wrapper(os.path.join(uicdir, "pyuic.py"), os.path.join("pyuic", "pyuic4"), gui, use_arch)

        sipconfig.inform("Creating pyuic4 Makefile...")

        makefile = sipconfig.PythonModuleMakefile(
            configuration=sipcfg,
            dstdir=uicdir,
            srcdir=os.path.join(src_dir, "pyuic", "uic"),
            dir="pyuic",
            installs=[[os.path.basename(wrapper), opts.pyqtbindir]]
        )

        makefile.generate()
        tool.append("pyuic")

        if "QtXml" in pyqt_modules:
            sipconfig.inform("Creating pylupdate4 Makefile...")

            makefile = sipconfig.ProgramMakefile(
                configuration=sipcfg,
                build_file=os.path.join(src_dir, "pylupdate", "pylupdate.sbf"),
                dir="pylupdate",
                install_dir=opts.pyqtbindir,
                console=1,
                qt=["QtCore", "QtGui", "QtXml"],
                debug=opts.debug,
                warnings=1,
                universal=sipcfg.universal,
                arch=sipcfg.arch
            )

            makefile.extra_include_dirs.append(os.path.join(src_dir, "pylupdate"))
            makefile.generate()
            tool.append("pylupdate")

            sipconfig.inform("Creating pyrcc4 Makefile...")

            makefile = pyrccMakefile()
            makefile.generate()
            tool.append("pyrcc")
        else:
            sipconfig.inform("pylupdate4 and pyrcc4 will not be built because the Qt XML module is missing.")

        if opts.designer_plugin and "QtDesigner" in pyqt_modules:
            py_major = sipcfg.py_version >> 16
            py_minor = (sipcfg.py_version >> 8) & 0x0ff

            if sys.platform == 'win32':
                lib_dir_flag = quote("-L%s" % sipcfg.py_lib_dir)
                link = "%s -lpython%d%d" % (lib_dir_flag, py_major, py_minor)
                pysh_lib = "python%d%d.dll" % (py_major, py_minor)
            else:
                # Use distutils to get the additional configuration.
                from distutils.sysconfig import get_config_vars
                ducfg = get_config_vars()

                if sys.platform == "darwin":
                    # We need to work out how to specify the right framework
                    # version.
                    link = "-framework Python"
                elif ("--enable-shared" in ducfg.get("CONFIG_ARGS", "") and
                      glob.glob("%s/lib/libpython%d.%d*" % (ducfg["exec_prefix"], py_major, py_minor))):
                    lib_dir_flag = quote("-L%s/lib" % ducfg["exec_prefix"])
                    link = "%s -lpython%d.%d" % (lib_dir_flag, py_major, py_minor)
                else:
                    sipconfig.inform("Qt Designer plugin disabled because Python library is static")
                    opts.designer_plugin = False

                pysh_lib = ducfg["LDLIBRARY"]

            if opts.designer_plugin:
                sipconfig.inform("Creating Qt Designer plugin Makefile...")

                # Run qmake to generate the Makefile.
                qmake_args = fix_qmake_args()
                cwd = os.getcwd()

                mk_clean_dir("designer", clean=0)
                os.chdir("designer")

                # Create the qmake project file.
                fin = open(os.path.join(src_dir, "designer", "python.pro-in"))
                prj = fin.read()
                fin.close()

                prj = prj.replace("@PYINCDIR@", quote(sipcfg.py_inc_dir))
                prj = prj.replace("@PYINCDIR@", " ".join((quote(sipcfg.py_conf_inc_dir), quote(sipcfg.py_inc_dir))))
                prj = prj.replace("@PYLINK@", link)
                prj = prj.replace("@PYSHLIB@", pysh_lib)
                prj = prj.replace("@QTPLUGINDIR@", quote(opts.plugindir + "/designer"))

                fout = open("python.pro", "w+")

                if sipcfg.arch:
                    fout.write(arch_config())

                if sipcfg.universal:
                    fout.write("QMAKE_MAC_SDK = %s\n" % sipcfg.universal)

                if src_dir != os.path.curdir:
                    fout.write("VPATH = %s\n" % os.path.join(src_dir, "designer"))

                fout.write(prj)
                fout.close()

                run_command("%s %s" % (opts.qmake, qmake_args))
                os.chdir(cwd)

                tool.append("designer")

        return tool


def arch_config():
    """Return the qmake CONFIG line for a MacOS binary."""

    qmake_archs = []
    for a in sipcfg.arch.split():
        if a == 'i386':
            qmake_archs.append('x86')
        elif a == 'x86_64':
            qmake_archs.append('x86_64')
        elif a == 'ppc':
            qmake_archs.append('ppc')

    return 'CONFIG += %s\n' % ' '.join(qmake_archs)


def quote(path):
    """Return a path with quotes added if it contains spaces."""
    if " " in path:
        path = '"%s"' % path

    return path


def inform_user():
    """Tell the user the option values that are going to be used.
    """
    if qt_edition:
        edstr = qt_edition + " edition "
    else:
        edstr = ""

    if qt_shared:
        lib_type = "shared"
    else:
        lib_type = "static"

    sipconfig.inform("Qt v%s %sis being used." % (sipconfig.version_to_string(qt_version), edstr))

    if qt_licensee:
        sipconfig.inform("Qt is licensed to %s." % qt_licensee)

    if sys.platform == "darwin" and qt_framework:
        sipconfig.inform("Qt is built as a framework.")

    sipconfig.inform("SIP %s is being used." % sipcfg.sip_version_str)
    sipconfig.inform("The Qt header files are in %s." % qt_incdir)
    sipconfig.inform("The %s Qt libraries are in %s." % (lib_type, qt_libdir))
    sipconfig.inform("The Qt binaries are in %s." % qt_bindir)
    sipconfig.inform("The Qt mkspecs directory is in %s." % qt_datadir)
    sipconfig.inform("These PyQt modules will be built: %s." % ", ".join(pyqt_modules))
    sipconfig.inform("The PyQt Python package will be installed in %s." % opts.pyqtmoddir)

    if opts.no_docstrings:
        sipconfig.inform("PyQt is being built without generated docstrings.")
    else:
        sipconfig.inform("PyQt is being built with generated docstrings.")

    if opts.prot_is_public:
        sipconfig.inform("PyQt is being built with 'protected' redefined as 'public'.")

    if opts.designer_plugin:
        sipconfig.inform("The Designer plugin will be installed in %s." % os.path.join(opts.plugindir, "designer"))

    if opts.api:
        sipconfig.inform("The QScintilla API file will be installed in %s." % os.path.join(opts.qscidir, "api", "python"))

    if pydbusmoddir:
        sipconfig.inform("The dbus support module will be installed in %s." % pydbusmoddir)

    sipconfig.inform("The PyQt .sip files will be installed in %s." % opts.pyqtsipdir)

    sipconfig.inform("pyuic4, pyrcc4 and pylupdate4 will be installed in %s." % opts.pyqtbindir)

    if opts.vendorcheck:
        sipconfig.inform("PyQt will only be usable with signed interpreters.")


def create_config(module, template, macros):
    """Create the PyQt configuration module so that it can be imported by build
    scripts.

    module is the module file name.
    template is the template file name.
    macros is the dictionary of platform specific build macros.
    """
    sipconfig.inform("Creating %s..." % module)

    content = {
        "pyqt_config_args":   sys.argv[1:],
        "pyqt_version":       pyqt_version,
        "pyqt_version_str":   pyqt_version_str,
        "pyqt_bin_dir":       opts.pyqtbindir,
        "pyqt_mod_dir":       pyqt_modroot,
        "pyqt_sip_dir":       opts.pyqtsipdir,
        "pyqt_modules":       pyqt_modules,
        "pyqt_sip_flags":     qt_sip_flags,
        "qt_version":         qt_version,
        "qt_edition":         qt_edition,
        "qt_winconfig":       qt_shared,
        "qt_framework":       qt_framework,
        "qt_threaded":        1,
        "qt_dir":             qt_dir,
        "qt_data_dir":        qt_datadir,
        "qt_inc_dir":         qt_incdir,
        "qt_lib_dir":         qt_libdir
    }

    sipconfig.create_config_module(module, template, content, macros)


def run_command(cmd):
    """Run a command and display the output if verbose mode is enabled.

    cmd is the command to run.
    """
    if opts.verbose:
        sys.stdout.write(cmd + "\n")

    fout = get_command_stdout(cmd, and_stderr=True)

    # Read stdout and stderr until there is no more output.
    lout = fout.readline()
    while lout:
        if opts.verbose:
            if sys.hexversion >= 0x03000000:
                sys.stdout.write(str(lout, encoding=sys.stdout.encoding))
            else:
                sys.stdout.write(lout)

        lout = fout.readline()

    fout.close()

    try:
        os.wait()
    except:
        pass


def remove_file(fname):
    """Remove a file which may or may not exist.

    fname is the name of the file.
    """
    try:
        os.remove(fname)
    except OSError:
        pass


def generate_OpenGL_extras():
    """Generate the extras needed by the QtOpenGL module (i.e. the .sip file
    defining the correct typedefs for the OpenGL data types.
    """
    sipconfig.inform("Determining the OpenGL data types...")

    src = "opengl_extras.cpp"

    f = open(src, "w")

    f.write(
"""#include <QFile>
#include <QTextStream>
#include <qgl.h>

int main(int, char **)
{
    QFile outf("./sip/QtOpenGL/opengl_types.sip");

    if (!outf.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        return 1;

    QTextStream out(&outf);

    if (sizeof (long) == sizeof (GLint))
        out << "typedef long GLint;\\n";
    else
        out << "typedef int GLint;\\n";

    if (sizeof (unsigned long) == sizeof (GLuint))
        out << "typedef unsigned long GLuint;\\n";
    else
        out << "typedef unsigned GLuint;\\n";

    if (sizeof (unsigned long) == sizeof (GLenum))
        out << "typedef unsigned long GLenum;\\n";
    else
        out << "typedef unsigned GLenum;\\n";

    if (sizeof (unsigned long) == sizeof (GLbitfield))
        out << "typedef unsigned long GLbitfield;\\n";
    else
        out << "typedef unsigned GLbitfield;\\n";

    out << "typedef float GLfloat;\\n";

    return 0;
}
""")

    f.close()

    cmd = compile_qt_program(src, "QtOpenGL")

    if cmd is None:
        sipconfig.error("Unable to determine the OpenGL data types.")

    # SIP's build system (specifically ProgramMakefile.build_command()) assumes
    # that an executable can be created by running a single command.  In the
    # case of MSVC this is incorrect.  As a quick hack we do the extra step
    # here if it looks like it is needed.
    if os.access("opengl_extras.manifest", os.F_OK):
        run_command("mt -nologo -manifest opengl_extras.manifest -outputresource:opengl_extras.exe;1")

    run_command(cmd)


def compile_qt_program(name, mname, extra_include_dirs=None, extra_lib_dirs=None, extra_libs=None):
    """Compile a simple Qt application.

    name is the name of the single source file.
    mname is the name of the Qt module.
    extra_include_dirs is an optional list of extra include directories.
    extra_lib_dirs is an optional list of extra library directories.
    extra_libs is an optional list of extra libraries.

    Returns the name of the executable suitable for running or None if it
    wasn't created.
    """
    opengl = (mname == "QtOpenGL")

    qt = [mname]
    if mname in ("QtOpenGL", "QtWebKit"):
        qt.append("QtCore")

    makefile = sipconfig.ProgramMakefile(sipcfg, console=1, qt=qt, warnings=0,
            opengl=opengl, debug=opts.debug, arch=sipcfg.arch)

    add_makefile_extras(makefile, extra_include_dirs, extra_lib_dirs, extra_libs)

    exe, build = makefile.build_command(name)

    # Make sure the executable file doesn't exist.
    remove_file(exe)
    run_command(build)

    #if not os.access(exe, os.X_OK):
    #    return None

    if sys.platform != 'win32':
        exe = "./" + exe

    return exe


def add_makefile_extras(makefile, extra_include_dirs, extra_lib_dirs, extra_libs):
    """Add any extra include or library directories or libraries to a makefile.

    makefile is the makefile.
    extra_include_dirs is the list of extra include directories.
    extra_lib_dirs is the list of extra library directories.
    extra_libs is the list of extra libraries.
    """
    if extra_include_dirs:
        makefile.extra_include_dirs.extend(extra_include_dirs)

    if extra_lib_dirs:
        makefile.extra_lib_dirs.extend(extra_lib_dirs)

    if extra_libs:
        makefile.extra_libs.extend(extra_libs)


def check_vendorid():
    """See if the VendorID library and include file can be found.
    """
    if opts.vendorcheck:
        if os.access(os.path.join(opts.vendincdir, "vendorid.h"), os.F_OK):
            if glob.glob(os.path.join(opts.vendlibdir, "*vendorid*")):
                sipconfig.inform("The VendorID package was found.")
            else:
                opts.vendorcheck = 0
                sipconfig.inform("The VendorID library could not be found in "
                                 "%s and so signed interpreter checking will "
                                 "be disabled. If the VendorID library is "
                                 "installed then use the -m argument to "
                                 "explicitly specify the correct "
                                 "directory." % opts.vendlibdir)
        else:
            opts.vendorcheck = 0
            sipconfig.inform("vendorid.h could not be found in %s and so "
                             "signed interpreter checking will be disabled. "
                             "If the VendorID package is installed then use "
                             "the -l argument to explicitly specify the "
                             "correct directory." % opts.vendincdir)


def get_command_stdout(cmd, and_stderr=False):
    """Return stdout (and optionally stderr) from the given command.
    """
    try:
        import subprocess
    except ImportError:
        if and_stderr:
            _, sout = os.popen4(cmd)
        else:
            _, sout, _ = os.popen3(cmd)

        return sout

    if and_stderr:
        stderr = subprocess.STDOUT
    else:
        stderr = subprocess.PIPE

    p = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE,
            stdout=subprocess.PIPE, stderr=stderr)

    return p.stdout


def check_dbus():
    """See if the DBus support module should be built.
    """
    sipconfig.inform("Checking to see if the dbus support module should be built...")

    sout = get_command_stdout("pkg-config --cflags-only-I --libs dbus-1")
    iflags = sout.read().strip()

    if not iflags:
        sipconfig.inform("DBus v1 does not seem to be installed.")
        return

    # Using str() means it will work with both Python v2 and v3.
    for f in str(iflags).split():
        if f.startswith("-I"):
            dbusincdirs.append(f[2:])
        elif f.startswith("-L"):
            dbuslibdirs.append(f[2:])
        elif f.startswith("-l"):
            dbuslibs.append(f[2:])

    try:
        import dbus.mainloop
    except:
        sipconfig.inform("The Python dbus module doesn't seem to be installed.")
        return

    global pydbusmoddir
    pydbusmoddir = dbus.mainloop.__path__[0]

    # Try and find dbus-python.h.  We don't use pkg-config because it is broken
    # for dbus-python (at least for versions up to and including v0.81.0).
    # Instead we look where DBus itself is installed - which in most cases will
    # be where dbus-python is also installed.
    if opts.pydbusincdir:
        dlist = [opts.pydbusincdir]
    else:
        dlist = dbusincdirs

    for d in dlist:
        if os.access(os.path.join(d, "dbus", "dbus-python.h"), os.F_OK):
            if d not in dbusincdirs:
                dbusincdirs.append(d)

            break
    else:
        sipconfig.inform("dbus/dbus-python.h could not be found and so the "
                         "DBus support module will be disabled. If "
                         "dbus-python v0.80 or later is installed then use "
                         "the -s argument to explicitly specify the directory "
                         "containing dbus/dbus-python.h.")
        pydbusmoddir = None


def check_module(mname, incfile, test, extra_include_dirs=None, extra_lib_dirs=None, extra_libs=None):
    """See if a module can be built and, if so, add it to the global list of
    modules.

    mname is the name of the module.
    incfile is the name of the include file needed for the test.
    test is a C++ statement being used for the test.
    extra_include_dirs is an optional list of extra include directories.
    extra_lib_dirs is an optional list of extra library directories.
    extra_libs is an optional list of extra libraries.
    """
    # Check that the module is enabled if we are not automatically enabling all
    # modules.
    if len(opts.enabled) > 0 and mname not in opts.enabled:
        return

    # Check the module's main .sip file exists.
    if os.access(os.path.join(src_dir, "sip", mname, mname + "mod.sip"), os.F_OK):
        sipconfig.inform("Checking to see if the %s module should be built..." % mname)

        if check_api(incfile, test, mname, extra_include_dirs=extra_include_dirs, extra_lib_dirs=extra_lib_dirs, extra_libs=extra_libs):
            pyqt_modules.append(mname)


def check_api(incfile, test, mname, extra_include_dirs=None, extra_lib_dirs=None, extra_libs=None):
    """Return non-zero if a class is available.

    incfile is the name of the include file needed for the test.
    test is a C++ statement being used for the test.
    mname is the name of the module.
    extra_include_dirs is an optional list of extra include directories.
    extra_lib_dirs is an optional list of extra library directories.
    extra_libs is an optional list of extra libraries.
    """
    # We use a module specific name to avoid a potential problem on Windows
    # where the operating system doesn't delete previous tests quickly enough.
    cfgtest = "cfgtest_%s.cpp" % mname

    f = open(cfgtest, "w")

    f.write("""#include <%s>

int main(int, char **)
{
    %s;
}
""" % (incfile, test))

    f.close()

    return compile_qt_program(cfgtest, mname,
            extra_include_dirs=extra_include_dirs,
            extra_lib_dirs=extra_lib_dirs, extra_libs=extra_libs)


def set_sip_flags(pyqt):
    """Set the SIP platform, version and feature flags.

    pyqt is the configuration instance.
    """
    # If we don't check for signed interpreters, we exclude the 'VendorID'
    # feature
    if not opts.vendorcheck:
        qt_sip_flags.append("-x")
        qt_sip_flags.append("VendorID")

    # Handle the platform tag.
    #if sys.platform == 'win32':
    #    plattag = "WS_WIN"
    #elif sys.platform == "darwin":
    #    if "__USE_WS_X11__" in sipcfg.build_macros()["DEFINES"]:
    #        plattag = "WS_X11"
    #    else:
    #        plattag = "WS_MACX"
    #else:
    plattag = "WS_QWS"

    qt_sip_flags.append("-t")
    qt_sip_flags.append(plattag)

    # Handle the Qt version tag.
    verstag = sipconfig.version_to_sip_tag(qt_version, pyqt.qt_version_tags(), "Qt")

    # Handle any feature flags.
    for xf in qt_xfeatures:
        qt_sip_flags.append("-x")
        qt_sip_flags.append(xf)

    if verstag:
        qt_sip_flags.append("-t")
        qt_sip_flags.append(verstag)

    # Handle the version specific Python features.
    if sipcfg.py_version < 0x020400:
        qt_sip_flags.append("-x")
        qt_sip_flags.append("Py_DateTime")

    if sipcfg.py_version < 0x030000:
        qt_sip_flags.append("-x")
        qt_sip_flags.append("Py_v3")

    # There is an issue creating QObjects while the GIL is held causing
    # deadlocks in multi-threaded applications.  We don't fully understand this
    # yet so we make sure we avoid the problem by always releasing the GIL.
    qt_sip_flags.append("-g")


def needed_qt_libs(mname, qt_libs):
    """Add any additional Qt libraries needed by a module to an existing list.

    mname is the name of the module.
    qt_libs is the current list of libraries.
    """

    # The dependencies between the different Qt libraries.  The order within
    # each list is important.  Note that this affects the include directories
    # as well as the libraries.
    LIB_DEPS = {
        "QtCore": [],
        "QtDeclarative": ["QtNetwork", "QtGui"],
        "QtGui": ["QtCore"],
        "QtHelp": ["QtGui"],
        "QtMultimedia": ["QtGui"],
        "QtNetwork": ["QtCore"],
        "QtOpenGL": ["QtGui"],
        "QtScript": ["QtCore"],
        "QtScriptTools": ["QtScript", "QtGui", "QtCore"],
        "QtSql": ["QtGui"],
        "QtSvg": ["QtGui"],
        "QtTest": ["QtGui"],
        "QtWebKit": ["QtNetwork", "QtGui"],
        "QtXml": ["QtCore"],
        "QtXmlPatterns": ["QtNetwork", "QtCore"],
        "phonon": ["QtGui"],
        "QtAssistant": ["QtNetwork", "QtGui"],
        "QtDesigner": ["QtGui"],
        "QAxContainer": ["QtGui"]
    }

    # Handle the dependencies first.
    for d in LIB_DEPS[mname]:
        needed_qt_libs(d, qt_libs)

    if mname not in qt_libs:
        qt_libs.insert(0, mname)


def mk_clean_dir(name, clean=1):
    """Create a clean (ie. empty) directory.

    name is the name of the directory.
    """
    if clean:
        try:
            shutil.rmtree(name)
        except:
            pass

    try:
        os.makedirs(name)
    except:
        if clean:
            sipconfig.error("Unable to create the %s directory." % name)


def generate_code(mname, extra_include_dirs=None, extra_lib_dirs=None, extra_libs=None, extra_sip_flags=None):
    """Generate the code for a module.

    mname is the name of the module to generate the code for.
    extra_include_dirs is an optional list of additional directories to add to
    the list of include directories.
    extra_lib_dirs is an optional list of additional directories to add to the
    list of library directories.
    extra_libs is an optional list of additional libraries to add to the list
    of libraries.
    extra_sip_flags is an optional list of additional flags to pass to SIP.
    """
    sipconfig.inform("Generating the C++ source for the %s module..." % mname)

    mk_clean_dir(mname)

    # Work out what Qt libraries need to be linked against and how SIP is
    # supposed to handle the consolidated module and its components.
    cons_args = []

    if opts.bigqt:
        if mname == "_qt":
            qt_libs = []

            for m in pyqt_modules:
                needed_qt_libs(m, qt_libs)
        else:
            if mname != "Qt":
                cons_args.append("-p")
                cons_args.append("PyQt4._qt")

            qt_libs = 0
    else:
        if mname == "Qt":
            qt_libs = 0
        else:
            qt_libs = []
            needed_qt_libs(mname, qt_libs)

    # Build the SIP command line.  Keyword argument support is enabled.
    argv = ['"' + "/home/tsheasha/GUC/Bachelors/android-python27/python-build/prebuilt/bin/sip" + '"', '-k']

    if not opts.no_docstrings:
        argv.append("-o");

    if opts.prot_is_public:
        argv.append("-P");

    argv.extend(qt_sip_flags)
    argv.extend(cons_args)

    if extra_sip_flags:
        argv.extend(extra_sip_flags)

    if opts.concat:
        argv.append("-j")
        argv.append(str(opts.split))

    if opts.tracing:
        argv.append("-r")

    if mname not in ("Qt", "_qt", "Qsci"):
        argv.append("-a")
        argv.append(mname + ".api")

    argv.append("-c")
    argv.append(mname)

    buildfile = os.path.join(mname, mname + ".sbf")
    argv.append("-b")
    argv.append(buildfile)

    argv.append("-I")
    argv.append(os.path.join(src_dir, "sip"))

    # Add the name of the .sip file keeping in mind SIP assumes POSIX style
    # path separators.  The Qt module's .sip file is generated by this script
    # and so will be in a different place if this is an out-of-tree build.
    if mname == "Qt":
        argv.append("sip/Qt/Qtmod.sip")
    else:
        drive, path = os.path.splitdrive(src_dir)
        parts = path.split(os.pathsep)
        parts.extend(["sip", mname, mname + "mod.sip"])
        argv.append(drive + "/".join(parts))

    cmd = " ".join(argv)

    if opts.verbose:
        sys.stdout.write(cmd + "\n")

    os.system(cmd)

    # Check the result.
    #if not os.access(buildfile, os.F_OK):
    #    sipconfig.error("Unable to create the C++ code.")

    # Generate the Makefile.
    sipconfig.inform("Creating the Makefile for the %s module..." % mname)

    installs = []

    if opts.install_sipfiles:
        sipfiles = []

        sipdir = os.path.join("sip", mname)
        if mname != "Qt":
            sipdir = os.path.join(src_dir, sipdir)
            rel_sipdir = sipdir
        else:
            rel_sipdir = os.path.join("..", sipdir)

        for s in glob.glob(os.path.join(sipdir, "*.sip")):
            sipfiles.append(os.path.join(rel_sipdir, os.path.basename(s)))

        installs.append([sipfiles, os.path.join(opts.pyqtsipdir, mname)])

    opengl = (mname == "QtOpenGL")

    makefile = sipconfig.SIPModuleMakefile(
        configuration=sipcfg,
        build_file=mname + ".sbf",
        dir=mname,
        install_dir=pyqt_modroot,
        installs=installs,
        qt=qt_libs,
        opengl=opengl,
        warnings=1,
        static=opts.static,
        debug=opts.debug,
        universal=sipcfg.universal,
        arch=sipcfg.arch,
        prot_is_public=opts.prot_is_public
    )

    add_makefile_extras(makefile, extra_include_dirs, extra_lib_dirs, extra_libs)

    makefile.generate()


def check_license():
    """Handle the validation of the PyQt license.
    """
    try:
        import license
        ltype = license.LicenseType
        lname = license.LicenseName

        try:
            lfile = license.LicenseFile
        except AttributeError:
            lfile = None
    except ImportError:
        ltype = None

    if ltype is None:
        ltype = "GPL"
        lname = "GNU General Public License"
        lfile = None

    sipconfig.inform("This is the %s version of PyQt %s (licensed under the %s) for Python %s on %s." % (ltype, pyqt_version_str, lname, sys.version.split()[0], sys.platform))

    # Common checks.
    if qt_licensee and ltype == "GPL":
        sipconfig.error("This version of PyQt and the commercial version of Qt have incompatible licenses.")

    # Confirm the license if not already done.
    if not opts.license_confirmed:
        if ltype == "GPL":
            loptions = """
Type '2' to view the GPL v2 license.
Type '3' to view the GPL v3 license.
"""
        else:
            loptions = """
Type 'L' to view the license.
"""

        sys.stdout.write(loptions)
        sys.stdout.write("""Type 'yes' to accept the terms of the license.
Type 'no' to decline the terms of the license.

""")

        while 1:
            sys.stdout.write("Do you accept the terms of the license? ")
            sys.stdout.flush()

            try:
                resp = sys.stdin.readline()
            except KeyboardInterrupt:
                raise SystemExit
            except:
                resp = ""

            resp = resp.strip().lower()

            if resp == "yes":
                break

            if resp == "no":
                sys.exit(0)

            if ltype == "GPL":
                if resp == "2":
                    os.system("more LICENSE.GPL2")
                elif resp == "3":
                    os.system("more LICENSE.GPL3")
            else:
                if resp == "l":
                    os.system("more LICENSE")

    # If there should be a license file then check it is where it should be.
    if lfile:
        if os.access(os.path.join(src_dir, "sip", lfile), os.F_OK):
            sipconfig.inform("Found the license file %s." % lfile)
        else:
            sipconfig.error("Please copy the license file %s to the sip directory." % lfile)


def get_build_macros(overrides):
    """Return the dictionary of platform specific build macros from the Qt
    installation.  Return None if any of the overrides was invalid.

    overrides is a list of macros overrides from the user.
    """
    # Get the name of the qmake configuration file to take the macros from.
    if "QMAKESPEC" in list(os.environ.keys()):
        fname = os.environ["QMAKESPEC"]

        if not os.path.dirname(fname):
            fname = os.path.join(qt_datadir, "mkspecs", fname)
    elif sys.platform == "darwin":
        # The Qt Mac binary installer defaults to xcode which we don't want.
        fname = os.path.join(qt_datadir, "mkspecs", "macx-g++")
    else:
        fname = os.path.join(qt_datadir, "mkspecs", "default")

    fname = os.path.join(fname, "qmake.conf")

    if not os.access(fname, os.F_OK):
        sipconfig.error("Unable to find the qmake configuration file %s. Use the QMAKESPEC environment variable to specify the correct platform." % fname)

    # Add the Qt specific macros to the default.
    names = list(sipcfg.build_macros().keys())
    names.append("INCDIR_QT")
    names.append("LIBDIR_QT")
    names.append("MOC")

    properties = {
        "QT_INSTALL_BINS":      qt_bindir,
        "QT_INSTALL_HEADERS":   qt_incdir,
        "QT_INSTALL_LIBS":      qt_libdir
    }

    return sipconfig.parse_build_macros(fname, names, overrides, properties)


def check_qt_installation(macros):
    """Check the Qt installation and get the version number and edition and
    return the configuration instance.

    macros is the dictionary of build macros.
    """
    # Check the Qt version number.
    if qt_version < 0x040100:
        sipconfig.error("PyQt v4 requires Qt v4.1.0 or later.")

    # Work out how Qt was built on MacOS.
    if sys.platform == "darwin":
        if os.access(os.path.join(qt_libdir, "QtCore.framework"), os.F_OK):
            global qt_framework
            qt_framework = 1

    # Get the Makefile generator.
    generator = macros["MAKEFILE_GENERATOR"]

    # We haven't yet factored out sipconfig's knowledge of how to build Qt
    # binaries and it is expecting to find these in the configuration when it
    # generates the Makefiles.
    sipcfg.qt_version = qt_version
    sipcfg.qt_edition = qt_edition
    sipcfg.qt_winconfig = qt_shared
    sipcfg.qt_framework = qt_framework
    sipcfg.qt_threaded = 1
    sipcfg.qt_dir = qt_dir
    sipcfg.qt_lib_dir = qt_libdir

    return ConfigurePyQt4(generator)


def fix_qmake_args(args=""):
    """Make any platform specific adjustments to the arguments passed to qmake.
    """
    if sys.platform == "darwin":
        # The Qt binary installer has macx-xcode as the default.
        args = "-spec %s %s" % (sipcfg.platform, args)

    return args


def get_qt_configuration():
    """Set the qt_dir, qt_incdir, qt_libdir, qt_bindir, qt_datadir,
    qt_pluginsdir and qt_xfeatures globals for the Qt installation.
    """
    sipconfig.inform("Determining the layout of your Qt installation...")

    # The file names we will use to get the directory information.
    app = "qtdirs"
    pro_file = app + ".pro"
    make_file = app + ".mk"
    make_target = ""
    cpp_file = app + ".cpp"
    out_file = app + ".out"
    qmake_args = fix_qmake_args("-o " + make_file)

    if sys.platform == 'win32':
        exe_file = os.path.join("release", app + ".exe")
        make_target = " release"
    elif sys.platform == "darwin":
        exe_file = os.path.join(app + ".app", "Contents", "MacOS", app)
    else:
        exe_file = os.path.join(".", app)

    # Generate the qmake project file.
    f = open(pro_file, "w")

    if sipcfg.arch:
        f.write(arch_config())

    f.write(
"""QT = core
# This is for certain broken Linux distros and is needed to make sure that
# QT_SHARED is properly defined.
CONFIG += link_prl
TARGET = %s
SOURCES = %s
""" % (app, cpp_file))

    f.close()

    # Generate the source code.
    f = open(cpp_file, "w")

    f.write(
"""#include <QFile>
#include <QLibraryInfo>
#include <QTextStream>

int main(int, char **)
{
    QFile outf("%s");

    if (!outf.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        return 1;

    QTextStream out(&outf);

    out << QLibraryInfo::location(QLibraryInfo::PrefixPath) << '\\n';
    out << QLibraryInfo::location(QLibraryInfo::HeadersPath) << '\\n';
    out << QLibraryInfo::location(QLibraryInfo::LibrariesPath) << '\\n';
    out << QLibraryInfo::location(QLibraryInfo::BinariesPath) << '\\n';
    out << QLibraryInfo::location(QLibraryInfo::DataPath) << '\\n';
    out << QLibraryInfo::location(QLibraryInfo::PluginsPath) << '\\n';

    out << QT_VERSION << '\\n';
    out << QT_EDITION << '\\n';

    out << QLibraryInfo::licensee() << '\\n';

#if defined(QT_SHARED) || defined(QT_DLL)
    out << "shared\\n";
#else
    out << "\\n";
#endif

    // Determine which features should be disabled.

#if defined(QT_NO_ACCESSIBILITY)
    out << "PyQt_Accessibility\\n";
#endif

#if defined(QT_NO_BIGCODECS)
    out << "PyQt_BigCodecs\\n";
#endif

#if defined(QT_NO_BUTTONGROUP)
    out << "PyQt_ButtonGroup\\n";
#endif

#if defined(QT_NO_CLIPBOARD)
    out << "PyQt_Clipboard\\n";
#endif

#if defined(QT_NO_CODECS)
    out << "PyQt_Codecs\\n";
#endif

#if defined(QT_NO_COLORDIALOG)
    out << "PyQt_ColorDialog\\n";
#endif

#if defined(QT_NO_COLORNAMES)
    out << "PyQt_ColorNames\\n";
#endif

#if defined(QT_NO_CONTEXTMENU)
    out << "PyQt_ContextMenu\\n";
#endif

#if defined(QT_NO_CURSOR)
    out << "PyQt_Cursor\\n";
#endif

#if defined(QT_NO_DIAL)
    out << "PyQt_Dial\\n";
#endif

#if defined(QT_NO_DIRECTPAINTER)
    out << "PyQt_DirectPainter\\n";
#endif

#if defined(QT_NO_DIRMODEL)
    out << "PyQt_DirModel\\n";
#endif

#if defined(QT_NO_DOCKWIDGET)
    out << "PyQt_DockWidget\\n";
#endif

#if defined(QT_NO_DOM)
    out << "PyQt_DOMClasses\\n";
#endif

#if defined(QT_NO_DRAGANDDROP)
    out << "PyQt_DragAndDrop\\n";
#endif

#if defined(QT_NO_ERRORMESSAGE)
    out << "PyQt_ErrorMessage\\n";
#endif

#if defined(QT_NO_FILEDIALOG)
    out << "PyQt_FileDialog\\n";
#endif

#if defined(QT_NO_FONTDIALOG)
    out << "PyQt_FontDialog\\n";
#endif

#if defined(QT_NO_IMAGEFORMATPLUGIN)
    out << "PyQt_ImageFormatPlugin\\n";
#endif

#if defined(QT_NO_IMAGEFORMAT_PPM)
    out << "PyQt_ImageFormat_PPM\\n";
#endif

#if defined(QT_NO_IMAGE_HEURISTIC_MASK)
    out << "PyQt_Image_Heuristic_Mask\\n";
#endif

#if defined(QT_NO_INPUTDIALOG)
    out << "PyQt_InputDialog\\n";
#endif

#if defined(QT_NO_IMAGE_TEXT)
    out << "PyQt_Image_Text\\n";
#endif

#if defined(QT_NO_ITEMVIEWS)
    out << "PyQt_ItemViews\\n";
#endif

#if defined(QT_NO_LCDNUMBER)
    out << "PyQt_LCDNumber\\n";
#endif

#if defined(QT_NO_LINEEDITMENU)
    out << "PyQt_LineEditMenu\\n";
#endif

#if defined(QT_NO_LISTVIEW)
    out << "PyQt_ListView\\n";
#endif

#if defined(QT_NO_LISTWIDGET)
    out << "PyQt_ListWidget\\n";
#endif

#if defined(QT_NO_MAINWINDOW)
    out << "PyQt_MainWindow\\n";
#endif

#if defined(QT_NO_MENU)
    out << "PyQt_Menu\\n";
#endif

#if defined(QT_NO_MENUBAR)
    out << "PyQt_MenuBar\\n";
#endif

#if defined(QT_NO_MESSAGEBOX)
    out << "PyQt_MessageBox\\n";
#endif

#if defined(QT_NO_NETWORKPROXY)
    out << "PyQt_NetworkProxy\\n";
#endif

#if defined(QT_NO_OPENSSL)
    out << "PyQt_OpenSSL\\n";
#endif

#if defined(QT_NO_PICTURE)
    out << "PyQt_Picture\\n";
#endif

#if defined(QT_NO_PRINTDIALOG)
    out << "PyQt_PrintDialog\\n";
#endif

#if defined(QT_NO_PRINTPREVIEWDIALOG)
    out << "PyQt_PrintPreviewDialog\\n";
#endif

#if defined(QT_NO_PRINTPREVIEWWIDGET)
    out << "PyQt_PrintPreviewWidget\\n";
#endif

#if defined(QT_NO_PRINTER)
    out << "PyQt_Printer\\n";
#endif

#if defined(QT_NO_PROGRESSDIALOG)
    out << "PyQt_ProgressDialog\\n";
#endif

#if defined(QT_NO_PROXYMODEL)
    out << "PyQt_ProxyModel\\n";
#endif

#if defined(QT_NO_RUBBERBAND)
    out << "PyQt_RubberBand\\n";
#endif

#if defined(QT_NO_PROCESS)
    out << "PyQt_Process\\n";
#endif

#if defined(QT_NO_QWS_ALPHA_CURSOR)
    out << "PyQt_QWS_Alpha_Cursor\\n";
#endif

#if defined(QT_NO_QWS_CURSOR)
    out << "PyQt_QWS_Cursor\\n";
#endif

#if defined(QT_NO_QWS_DECORATION_WINDOWS)
    out << "PyQt_QWS_Decoration_Windows\\n";
#endif

#if defined(QT_NO_QWS_MOUSE)
    out << "PyQt_QWS_Mouse\\n";
#endif

#if defined(QT_NO_QWS_MOUSE_AUTO)
    out << "PyQt_QWS_Mouse_Auto\\n";
#endif

#if defined(QT_NO_QWS_MOUSE_MANUAL)
    out << "PyQt_QWS_Mouse_Manual\\n";
#endif

#if defined(QT_NO_RUBBERBAND)
    out << "PyQt_RubberBand\\n";
#endif

#if defined(QT_NO_SCROLLBAR)
    out << "PyQt_ScrollBar\\n";
#endif

#if defined(QT_NO_SESSIONMANAGER)
    out << "PyQt_SessionManager\\n";
#endif

#if defined(QT_NO_SIZEGRIP)
    out << "PyQt_SizeGrip\\n";
#endif

#if defined(QT_NO_SOCKS5)
    out << "PyQt_Socks5\\n";
#endif

#if defined(QT_NO_SORTFILTERPROXYMODEL)
    out << "PyQt_SortFilterProxyModel\\n";
#endif

#if defined(QT_NO_SPLASHSCREEN)
    out << "PyQt_SplashScreen\\n";
#endif

#if defined(QT_NO_SPLITTER)
    out << "PyQt_Splitter\\n";
#endif

#if defined(QT_NO_STANDARDITEMMODEL)
    out << "PyQt_StandardItemModel\\n";
#endif

#if defined(QT_NO_STATUSBAR)
    out << "PyQt_StatusBar\\n";
#endif

#if defined(QT_NO_STATUSTIP)
    out << "PyQt_StatusTip\\n";
#endif

#if defined(QT_NO_STRINGLISTMODEL)
    out << "PyQt_StringListModel\\n";
#endif

#if defined(QT_NO_STYLE_CDE)
    out << "PyQt_Style_CDE\\n";
#endif

#if defined(QT_NO_STYLE_MOTIF)
    out << "PyQt_Style_Motif\\n";
#endif

#if defined(QT_NO_STYLE_PLASTIQUE)
    out << "PyQt_Style_Plastique\\n";
#endif

#if defined(QT_NO_STYLE_WINDOWSXP)
    out << "PyQt_Style_WindowsXP\\n";
#endif

#if defined(QT_NO_SYNTAXHIGHLIGHTER)
    out << "PyQt_SyntaxHighlighter\\n";
#endif

#if defined(QT_NO_SYSTEMTRAYICON)
    out << "PyQt_SystemTrayIcon\\n";
#endif

#if defined(QT_NO_TABBAR)
    out << "PyQt_TabBar\\n";
#endif

#if defined(QT_NO_TABDIALOG)
    out << "PyQt_TabDialog\\n";
#endif

#if defined(QT_NO_TABWIDGET)
    out << "PyQt_TabWidget\\n";
#endif

#if defined(QT_NO_TABLEVIEW)
    out << "PyQt_TableView\\n";
#endif

#if defined(QT_NO_TEXTEDITMENU)
    out << "PyQt_TextEditMenu\\n";
#endif

#if defined(QT_NO_THREAD)
    out << "PyQt_Thread\\n";
#endif

#if defined(QT_NO_TOOLBAR)
    out << "PyQt_ToolBar\\n";
#endif

#if defined(QT_NO_TOOLBOX)
    out << "PyQt_ToolBox\\n";
#endif

#if defined(QT_NO_TOOLBUTTON)
    out << "PyQt_ToolButton\\n";
#endif

#if defined(QT_NO_TOOLTIP)
    out << "PyQt_ToolTip\\n";
#endif

#if defined(QT_NO_TRANSLATION)
    out << "PyQt_Translator\\n";
#endif

#if defined(QT_NO_WHATSTHIS)
    out << "PyQt_WhatsThis\\n";
#endif

#if defined(QT_NO_WHEELEVENT)
    out << "PyQt_WheelEvent\\n";
#endif

#if defined(QT_NO_WORKSPACE)
    out << "PyQt_Workspace\\n";
#endif

#if !defined(QT3_SUPPORT) || QT_VERSION >= 0x040200
    out << "PyQt_NoPrintRangeBug\\n";
#endif

#if defined(QT_OPENGL_ES)
    out << "PyQt_NoOpenGLES\\n";
#endif

    if (sizeof (qreal) != sizeof (double))
        out << "PyQt_qreal_double\\n";

    return 0;
}
""" % out_file)

    f.close()

    # Create the makefile, first making sure it doesn't already exist.
    #remove_file(make_file)
    run_command("%s %s %s" % (opts.qmake, qmake_args, pro_file))

    #if not os.access(make_file, os.F_OK):
    #    sipconfig.error("%s failed to create a makefile. %s" % (opts.qmake, MSG_CHECK_QMAKE))

    # Try and work out the name of make.
    if sipcfg.platform.startswith("win32-msvc"):
        make = "nmake"
    elif sipcfg.platform == "win32-borland":
        make = "bmake"
    elif sipcfg.platform == "win32-g++":
        make = "mingw32-make"
    else:
        make = "make"

    # Create the executable, first making sure it doesn't exist.
    #remove_file(exe_file)
    run_command("%s -f %s%s" % (make, make_file, make_target))

    #if not os.access(exe_file, os.X_OK):
    #    sipconfig.error("Failed to determine the layout of your Qt installation. Try again using the --verbose flag to see more detail about the problem.")

    # Create the output file, first making sure it doesn't exist.
    #remove_file(out_file)
    run_command(exe_file)

    #if not os.access(out_file, os.F_OK):
    #    sipconfig.error("%s failed to create %s. Make sure your Qt v4 installation is correct." % (exe_file, out_file))

    # Read the directories.
    f = open(out_file, "r")
    lines = f.read().strip().split("\n")
    f.close()

    global qt_dir, qt_incdir, qt_libdir, qt_bindir, qt_datadir, qt_pluginsdir
    global qt_version, qt_edition, qt_licensee, qt_shared, qt_xfeatures

    qt_dir = lines[0]
    qt_incdir = lines[1]
    qt_libdir = lines[2]
    qt_bindir = lines[3]
    qt_datadir = lines[4]
    qt_pluginsdir = lines[5]
    qt_version = lines[6]
    qt_edition = lines[7]
    qt_licensee = lines[8]
    qt_shared = lines[9]
    qt_xfeatures = lines[10:]

    if opts.assume_shared:
        qt_shared = "shared"

    # 'Nokia' is the value that is used by Maemo's version of Qt.
    if qt_licensee in ('Open Source', 'Nokia'):
        qt_licensee = None

    try:
        qt_version = int(qt_version)
    except ValueError:
        sipconfig.error("QT_VERSION should be a number but \"%s\" was found." % qt_version)

    try:
        qt_edition = int(qt_edition)
    except ValueError:
        sipconfig.error("QT_EDITION should be a number but \"%s\" was found." % qt_edition)

    # Now convert the edition to a descriptive string.  The order of testing is
    # important.
    if qt_edition & 0x200:
        # It has ActiveQt.
        qt_edition = "Desktop"

        # ActiveQt became part of the open source version in v4.5.2.
        if qt_version >= 0x040502 and qt_licensee is None:
            qt_edition = "free"
    elif qt_edition & 0x008:
        # It has OpenGL.
        qt_edition = "free"
    elif qt_edition & 0x002:
        # It has GUI.
        qt_edition = "Desktop Light"
    else:
        qt_edition = "Console"

    if qt_shared:
        if opts.staticplugins:
            sipconfig.inform("Static plugins are disabled because Qt has been built as shared libraries.")
            opts.staticplugins = []
    else:
        if opts.static or opts.bigqt:
            pass
        else:
            sipconfig.error("Qt has been built as static libraries so either the -g or -k argument should be used.")


def main():
    """Create the configuration module module.
    """
    # Check SIP is new enough.
    if sipcfg.sip_version < sip_min_version:
        sipconfig.error("This version of PyQt requires SIP v%s or later" % sipconfig.version_to_string(sip_min_version))

    global opts

    # Parse the command line.
    p = create_optparser()
    opts, args = p.parse_args()

    # Provide defaults for platform-specific options.
    if sys.platform == 'win32':
        opts.qmake = find_default_qmake()
        opts.prot_is_public = False

    if not opts.qmake:
        sipconfig.error(MSG_CHECK_QMAKE)

    # Where the modules will be placed.
    global pyqt_modroot
    pyqt_modroot = os.path.join(opts.pyqtmoddir, "PyQt4")

    # When building static libraries, signed interpreter checking makes no
    # sense.
    if opts.vendorcheck and opts.static:
        sipconfig.error("Using the VendorID package when building static libraries makes no sense.")

    # Get the details of the Qt installation.
    get_qt_configuration()

    # Provide some defaults that are based on the Qt configuration.
    if not opts.plugindir:
        opts.plugindir = qt_pluginsdir

    if opts.qscidir:
        # An explicit directory implies installing the API file.
        opts.api = True
    else:
        opts.qscidir = os.path.join(qt_datadir, "qsci")

        if opts.api is None:
            # Install the API file if the default directory exists.
            opts.api = os.path.isdir(opts.qscidir)

    # Replace the existing build macros with the ones from the Qt installation.
    macros = get_build_macros(args)

    if macros is None:
        p.print_help()
        sys.exit(2)

    sipcfg.set_build_macros(macros)

    # Check Qt is what we need.
    pyqt = check_qt_installation(macros)

    # Check the licenses are compatible.
    check_license()

    # Check which modules to build.
    pyqt.check_modules()

    # Check for the VendorID package.
    check_vendorid()

    # Set the SIP platform, version and feature flags.
    set_sip_flags(pyqt)

    # Tell the user what's been found.
    inform_user()

    # Generate the code.
    pyqt.code()

    # Create the additional Makefiles.
    sipconfig.inform("Creating top level Makefile...")

    installs=[(pyqt.module_installs(), pyqt_modroot)]

    if opts.api:
        installs.append(("PyQt4.api", os.path.join(opts.qscidir, "api", "python")))

    xtra_modules = ["Qt"]

    if opts.bigqt:
        xtra_modules.append("_qt")

        if opts.mwg_qsci_dir:
            xtra_modules.append("Qsci")

        if opts.mwg_qwt_dir:
            xtra_modules.append("Qwt5")

    sipconfig.ParentMakefile(
        configuration=sipcfg,
        subdirs=pyqt.qpy_libs() + pyqt_modules + xtra_modules + pyqt.tools(),
        installs=installs
    ).generate()

    # Install the configuration module.
    create_config("pyqtconfig.py", os.path.join(src_dir, "pyqtconfig.py.in"),
            macros)


###############################################################################
# The script starts here.
###############################################################################

if __name__ == "__main__":
    try:
        main()
    except SystemExit:
        raise
    except:
        sys.stderr.write(
"""An internal error occured.  Please report all the output from the program,
including the following traceback, to support@riverbankcomputing.com.
""")
        raise
