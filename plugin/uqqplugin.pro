TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR = UQQ
TARGET = uqq

OBJECTS_DIR = tmp
MOC_DIR = tmp


SOURCES += uqqclient.cpp \
           uqqplugin.cpp

HEADERS += uqqclient.h \
           uqqplugin.h

OTHER_FILES += \
    json.txt

