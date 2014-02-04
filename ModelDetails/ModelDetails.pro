#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T13:09:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport

TARGET = ModelDetails
TEMPLATE = app


SOURCES += main.cpp\
        dscmodeldetails.cpp \
    drdiagrammanager.cpp

HEADERS  += dscmodeldetails.h \
    drdiagrammanager.h

FORMS    += dscmodeldetails.ui \
    drdiagrammanager.ui

RESOURCES += \
    Resources.qrc
