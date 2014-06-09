#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T08:52:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Datasets
TEMPLATE = app


SOURCES += main.cpp\
        datasetmetadata.cpp \
    inputdatatype.cpp \
    inputdatatextfile.cpp \
    inputdatadatabase.cpp \
    inputdataembedded.cpp

HEADERS  += datasetmetadata.h \
    inputdatatype.h \
    inputdatatextfile.h \
    inputdatadatabase.h \
    inputdataembedded.h

FORMS    += datasetmetadata.ui \
    inputdatatype.ui \
    inputdatatextfile.ui \
    inputdatadatabase.ui \
    inputdataembedded.ui

RESOURCES += \
    Resources.qrc
