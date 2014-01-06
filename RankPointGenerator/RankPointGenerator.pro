#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T14:36:14
#
#-------------------------------------------------

QT       -= gui
CONFIG += c++11
TARGET = RankPointGenerator
TEMPLATE = lib

DEFINES += RANKPOINTGENERATOR_LIBRARY

SOURCES += rankpointgenerator.cpp \
    management.cpp

HEADERS += rankpointgenerator.h\
        rankpointgenerator_global.h \
    management.h \
    dsc.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
