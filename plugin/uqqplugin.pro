TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR = UQQ
TARGET = uqq

OBJECTS_DIR = tmp
MOC_DIR = tmp


SOURCES += uqqclient.cpp \
           uqqplugin.cpp \
    uqqcontact.cpp

HEADERS += uqqclient.h \
           uqqplugin.h \
    uqqcontact.h

OTHER_FILES += \
    loginSuccess.txt

