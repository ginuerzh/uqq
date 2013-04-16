TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR = UQQ
TARGET = uqq

OBJECTS_DIR = tmp
MOC_DIR = tmp


SOURCES += uqqclient.cpp \
           uqqplugin.cpp \
    uqqcontact.cpp \
    uqqmember.cpp \
    uqqcategory.cpp \
    uqqmessage.cpp \
    uqqmemberdetail.cpp \
    uqqgroup.cpp \
    uqqgroupinfo.cpp

HEADERS += uqqclient.h \
           uqqplugin.h \
    uqqcontact.h \
    uqqmember.h \
    uqqcategory.h \
    uqqmessage.h \
    uqqmemberdetail.h \
    uqqgroup.h \
    uqqgroupinfo.h

OTHER_FILES += \
    loginSuccess.txt

