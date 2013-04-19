QT = core
# This is for certain broken Linux distros and is needed to make sure that
# QT_SHARED is properly defined.
CONFIG += link_prl
TARGET = qtdirs
SOURCES = qtdirs.cpp
