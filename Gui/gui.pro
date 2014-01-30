#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T14:29:32
#
#-------------------------------------------------

QT += core gui enginio

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = DatasetRanker
TEMPLATE = app


SOURCES += main.cpp\
           datasetclassification.cpp \
           formmodel.cpp \
           drmanagement.cpp \
    drinputtypes.cpp \
    drcroptab.cpp

HEADERS += datasetclassification.h \
           formmodel.h \
           dr.h \
           drmanagement.h \
    drinputtypes.h \
    drcroptab.h

FORMS   += datasetclassification.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RankPointGenerator/release/ -lRankPointGenerator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RankPointGenerator/debug/ -lRankPointGenerator
else:unix: LIBS += -L$$OUT_PWD/../RankPointGenerator/ -lRankPointGenerator

INCLUDEPATH += $$PWD/../RankPointGenerator
DEPENDPATH  += $$PWD/../RankPointGenerator

RESOURCES += Resources.qrc

OTHER_FILES += ../Gui/gold.png \
               ../Gui/platinum.png \
               ../Gui/register.png \
               ../Gui/silver.png
