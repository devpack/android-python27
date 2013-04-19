# This is the qmake project file for the QPy support code for the QtCore
# module.
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


CONFIG      += static
TARGET      = qpycore
TEMPLATE    = lib

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    win32: TARGET = $$join(TARGET,,d)
}

# Python's type system relies on type punning.
!win32: QMAKE_CXXFLAGS += -fno-strict-aliasing

# This seems to be necessary for Qt v4.5.2.
win32: INCLUDEPATH += .

SOURCES   = \
            qpycore_chimera.cpp \
            qpycore_chimera_signature.cpp \
            qpycore_chimera_storage.cpp \
            qpycore_init.cpp \
            qpycore_misc.cpp \
            qpycore_post_init.cpp \
            qpycore_pyqtboundsignal.cpp \
            qpycore_pyqtconfigure.cpp \
            qpycore_pyqtproperty.cpp \
            qpycore_pyqtproxy.cpp \
            qpycore_pyqtpyobject.cpp \
            qpycore_pyqtsignal.cpp \
            qpycore_pyqtslot.cpp \
            qpycore_qmetaobject.cpp \
            qpycore_qmetaobject_helpers.cpp \
            qpycore_qobject_helpers.cpp \
            qpycore_qstring.cpp \
            qpycore_qstringlist.cpp \
            qpycore_sip_helpers.cpp \
            qpycore_types.cpp \
            qpycore_qvariant.cpp

HEADERS   = \
            qpycore_api.h \
            qpycore_chimera.h \
            qpycore_misc.h \
            qpycore_pyqtboundsignal.h \
            qpycore_pyqtproperty.h \
            qpycore_pyqtproxy.h \
            qpycore_pyqtpyobject.h \
            qpycore_pyqtsignal.h \
            qpycore_qobject_helpers.h \
            qpycore_sip.h \
            qpycore_sip_helpers.h \
            qpycore_types.h
