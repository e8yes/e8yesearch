GG#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T21:53:10
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_unittest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

macx {
        INCLUDEPATH += /usr/local/include
        LIBS += -L/usr/local/lib
        LIBS += -lboost_system-mt -lboost_filesystem-mt
}

unix:!macx {
        LIBS += -lboost_system -lboost_filesystem
}

LIBS += -L$$PWD/../build-e8yesearch -le8yesearch

LIBS += -lcppcms -lbooster
LIBS += -lxerces-c
LIBS += -lcppdb
LIBS += -ljson

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''

INCLUDEPATH += $$PWD/../build-e8yesearch
DEPENDPATH += $$PWD/../build-e8yesearch
