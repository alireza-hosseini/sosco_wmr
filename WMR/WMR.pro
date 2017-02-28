#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T21:28:54
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = WMR
TEMPLATE = lib

DEFINES += WMR_LIBRARY

SOURCES += src/wmr.cpp \
    src/wmrrobotconnector.cpp \
    src/wmrsettings.cpp \
    src/wmrrobot.cpp \
    src/wmrudpconnection.cpp \
    src/statusreceiver.cpp

HEADERS += include/wmr.h\
    include/wmrrobotconnector.h \
    include/wmrsettings.h \
    include/wmrrobot.h \
    include/wmrudpconnection.h \
    include/WmrMovementProtocol.h \
    include/BasicUtils.h \
    include/statusreceiver.h \
    include/WmrPose.h \
    include/WmrSharpSensorProtocol.h

unix {
    DESTDIR = lib/
    includetarget.path = /usr/include/WMR
    includetarget.files = include/*.h
    target.path = /usr/lib
    INSTALLS += target includetarget

}
