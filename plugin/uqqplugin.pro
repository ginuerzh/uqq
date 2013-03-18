TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR = UQQ
TARGET = uqqplugin

OBJECTS_DIR = tmp
MOC_DIR = tmp


SOURCES += httpclient.cpp \
           uqqplugin.cpp

HEADERS += httpclient.h \
           uqqplugin.h

