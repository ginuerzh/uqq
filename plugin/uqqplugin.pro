TEMPLATE = lib
CONFIG += qt plugin debug
QT += qml

#DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT # no debug and warning output
DEFINES += QT_NO_EXCEPTIONS="1"

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

