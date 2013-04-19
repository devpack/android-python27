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
#
# This module is intended to be used by the configuration scripts of extension
# modules that %Import PyQt4 modules.


import sipconfig


# These are installation specific values created when PyQt4 was configured.
_pkg_config = {
    'pyqt_bin_dir':      '/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/bin',
    'pyqt_config_args':  '--no-designer-plugin --no-qsci-api --no-docstrings --bindir ../output/python/bin/ --destdir ../output/extras/python/site-packages/ -q /opt/necessitas/Android/Qt/480/armeabi/bin/qmake --confirm-license --no-sip-files',
    'pyqt_mod_dir':      '/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/PyQt4',
    'pyqt_modules':      'QtCore QtGui QtHelp QtMultimedia QtNetwork QtDeclarative QtOpenGL QtScript QtScriptTools QtSql QtSvg QtTest QtWebKit QtXml QtXmlPatterns phonon QtAssistant QtDesigner',
    'pyqt_sip_dir':      '/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/share/PyQt4',
    'pyqt_sip_flags':    '-x VendorID -t WS_QWS -x PyQt_NoPrintRangeBug -t Qt_4_7_0 -x Py_v3 -g',
    'pyqt_version':      0x040800,
    'pyqt_version_str':  '4.8',
    'qt_data_dir':       '/opt/necessitas/Android/Qt/480/armeabi',
    'qt_dir':            '/opt/necessitas',
    'qt_edition':        'free',
    'qt_framework':      0,
    'qt_inc_dir':        '/opt/necessitas/Android/Qt/480/armeabi/include',
    'qt_lib_dir':        '/opt/necessitas/Android/Qt/480/armeabi/lib',
    'qt_threaded':       1,
    'qt_version':        0x040801,
    'qt_winconfig':      'shared'
}

_default_macros = {
    'AIX_SHLIB':                '',
    'AR':                       '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-ar cqs',
    'CC':                       '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc',
    'CFLAGS':                   '-pipe',
    'CFLAGS_CONSOLE':           '',
    'CFLAGS_DEBUG':             '-g -marm -O0 -fno-omit-frame-pointer',
    'CFLAGS_EXCEPTIONS_OFF':    '',
    'CFLAGS_EXCEPTIONS_ON':     '',
    'CFLAGS_MT':                '',
    'CFLAGS_MT_DBG':            '',
    'CFLAGS_MT_DLL':            '',
    'CFLAGS_MT_DLLDBG':         '',
    'CFLAGS_RELEASE':           '-g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64',
    'CFLAGS_RTTI_OFF':          '',
    'CFLAGS_RTTI_ON':           '',
    'CFLAGS_SHLIB':             '-fPIC',
    'CFLAGS_STL_OFF':           '',
    'CFLAGS_STL_ON':            '',
    'CFLAGS_THREAD':            '-D_REENTRANT',
    'CFLAGS_WARN_OFF':          '-Wno-psabi',
    'CFLAGS_WARN_ON':           '-Wall -Wno-psabi -W',
    'CHK_DIR_EXISTS':           'if not exist',
    'CONFIG':                   'qt warn_on release link_prl ashmem android android_qtmain android_install  ',
    'COPY':                     'copy /y',
    'CXX':                      '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++',
    'CXXFLAGS':                 '-pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -pipe -DQT_NO_QWS_TRANSFORMED -DQ_WS_QWS --sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-5/arch-arm/ -fpic -g -msoft-float -mthumb -mthumb-interwork -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -msoft-float -mthumb -mthumb-interwork  -mtune=xscale -march=armv5te -mfloat-abi=softfp -mfpu=vfp -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wall -Wno-psabi -W -Os -pipe -msoft-float -fpic -mthumb-interwork -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums -funwind-tables -DANDROID  -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5TE__ -D__STDC_INT64__ -DQT_NO_QWS_TRANSFORMED',
    'CXXFLAGS_CONSOLE':         '',
    'CXXFLAGS_DEBUG':           '-g -marm -O0 -fno-omit-frame-pointer -g -marm -O0 -fno-omit-frame-pointer',
    'CXXFLAGS_EXCEPTIONS_OFF':  '',
    'CXXFLAGS_EXCEPTIONS_ON':   '',
    'CXXFLAGS_MT':              '',
    'CXXFLAGS_MT_DBG':          '',
    'CXXFLAGS_MT_DLL':          '',
    'CXXFLAGS_MT_DLLDBG':       '',
    'CXXFLAGS_RELEASE':         '-g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -g -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64',
    'CXXFLAGS_RTTI_OFF':        '',
    'CXXFLAGS_RTTI_ON':         '',
    'CXXFLAGS_SHLIB':           '-fPIC',
    'CXXFLAGS_STL_OFF':         '',
    'CXXFLAGS_STL_ON':          '',
    'CXXFLAGS_THREAD':          '-D_REENTRANT',
    'CXXFLAGS_WARN_OFF':        '-Wno-psabi',
    'CXXFLAGS_WARN_ON':         '-Wall -Wno-psabi -W',
    'DEFINES':                  '',
    'DEL_FILE':                 'del /q 2> NUL',
    'EXTENSION_PLUGIN':         '',
    'EXTENSION_SHLIB':          '',
    'INCDIR':                   ' /opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/include /opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/include /opt/necessitas/Android/Qt/480/qt-src/src/3rdparty/phonon',
    'INCDIR_OPENGL':            '',
    'INCDIR_QT':                '/opt/necessitas/Android/Qt/480/armeabi/include',
    'INCDIR_X11':               '',
    'LFLAGS':                   '--sysroot=/opt/necessitas/android-ndk-r6b/platforms/android-9/arch-arm/ -L/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/ -Wl,-rpath-link= -Wl,-rpath=/opt/necessitas/Android/Qt/480/qt-src/src/3rdparty/android/precompiled/android-9/arch-arm/lib -Wl,-z,noexecstack -Wl,-O1  -Wl,-z,noexecstack -shared -Wl,-shared,-Bsymbolic -Wl,--no-whole-archive',
    'LFLAGS_CONSOLE':           '',
    'LFLAGS_CONSOLE_DLL':       '',
    'LFLAGS_DEBUG':             '',
    'LFLAGS_DLL':               '',
    'LFLAGS_OPENGL':            '',
    'LFLAGS_PLUGIN':            '-Wl,--no-undefined -Wl,-z,noexecstack -shared -Wl,-z,noexecstack -Wl,-O1  -Wl,-z,noexecstack -shared -Wl,-shared,-Bsymbolic -Wl,--no-whole-archive  ',
    'LFLAGS_RELEASE':           '',
    'LFLAGS_RPATH':             '-Wl,-rpath=',
    'LFLAGS_SHLIB':             '-Wl,--no-undefined -Wl,-z,noexecstack -shared -Wl,-z,noexecstack -Wl,-O1  -Wl,-z,noexecstack -shared -Wl,-shared,-Bsymbolic -Wl,--no-whole-archive  ',
    'LFLAGS_SONAME':            '',
    'LFLAGS_THREAD':            '',
    'LFLAGS_WINDOWS':           '',
    'LFLAGS_WINDOWS_DLL':       '',
    'LIB':                      '',
    'LIBDIR':                   '/opt/necessitas/android-ndk-r6b/sources/cxx-stl-4.4.3/gnu-libstdc++/libs/armeabi/ ',
    'LIBDIR_OPENGL':            '',
    'LIBDIR_QT':                '/opt/necessitas/Android/Qt/480/armeabi/lib',
    'LIBDIR_X11':               '',
    'LIBS':                     '-lstdc++ -lsupc++ -llog -lz -lm -ldl -lc -lgcc -L/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/python/lib/ -lpython2.7',
    'LIBS_CONSOLE':             '',
    'LIBS_CORE':                '',
    'LIBS_GUI':                 '',
    'LIBS_NETWORK':             '',
    'LIBS_OPENGL':              '',
    'LIBS_RT':                  '',
    'LIBS_RTMT':                '',
    'LIBS_THREAD':              '',
    'LIBS_WEBKIT':              '',
    'LIBS_WINDOWS':             '',
    'LIBS_X11':                 '',
    'LINK':                     '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++',
    'LINK_SHLIB':               '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++',
    'LINK_SHLIB_CMD':           '',
    'MAKEFILE_GENERATOR':       'UNIX',
    'MKDIR':                    'mkdir',
    'MOC':                      '/opt/necessitas/Android/Qt/480/armeabi/bin/moc',
    'RANLIB':                   '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-ranlib',
    'RPATH':                    '',
    'STRIP':                    '/opt/necessitas/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-strip'
}


class Configuration(sipconfig.Configuration):
    """The class that represents PyQt configuration values.
    """
    def __init__(self, sub_cfg=None):
        """Initialise an instance of the class.

        sub_cfg is the list of sub-class configurations.  It should be None
        when called normally.
        """
        if sub_cfg:
            cfg = sub_cfg
        else:
            cfg = []

        cfg.append(_pkg_config)

        sipconfig.Configuration.__init__(self, cfg)


class QtCoreModuleMakefile(sipconfig.SIPModuleMakefile):
    """The Makefile class for modules that %Import QtCore.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore"]

        sipconfig.SIPModuleMakefile.__init__(self, *args, **kw)


class QtGuiModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtGui.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtHelpModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtHelp.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtHelp"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtMultimediaModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtMultimedia.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtMultimedia"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtNetworkModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtNetwork.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtNetwork"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtDeclarativeModuleMakefile(QtNetworkModuleMakefile):
    """The Makefile class for modules that %Import QtDeclarative.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtNetwork", "QtDeclarative"]

        QtNetworkModuleMakefile.__init__(self, *args, **kw)


class QtAssistantModuleMakefile(QtNetworkModuleMakefile):
    """The Makefile class for modules that %Import QtAssistant.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtNetwork", "QtAssistant"]

        QtNetworkModuleMakefile.__init__(self, *args, **kw)


class QtOpenGLModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtOpenGL.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        kw["opengl"] = 1

        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtOpenGL"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtScriptModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtScript.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtScript"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtScriptToolsModuleMakefile(QtScriptModuleMakefile):
    """The Makefile class for modules that %Import QtScriptTools.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtScript", "QtScriptTools"]

        QtScriptModuleMakefile.__init__(self, *args, **kw)


class QtSqlModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtSql.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtSql"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtSvgModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtSvg.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtSvg"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtTestModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtTest.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtTest"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtWebKitModuleMakefile(QtNetworkModuleMakefile):
    """The Makefile class for modules that %Import QtWebKit.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtNetwork", "QtWebKit"]

        QtNetworkModuleMakefile.__init__(self, *args, **kw)


class QtXmlModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtXml.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtXml"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtXmlPatternsModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtXmlPatterns.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtXmlPatterns"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class phononModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import phonon.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "phonon"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtDesignerModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtDesigner.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QtDesigner"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QAxContainerModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QAxContainer.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if "qt" not in kw:
            kw["qt"] = ["QtCore", "QtGui", "QAxContainer"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)
