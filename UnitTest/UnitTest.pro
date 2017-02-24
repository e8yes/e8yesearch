#-------------------------------------------------
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

unix:!macx {
LIBS += -L../build-e8yesearch-Desktop-Debug -le8yesearch
}

macx {
LIBS += -L$$PWD/../../build-e8yesearch-Desktop_Qt_5_7_0_GCC_64bit-Debug/ -le8yesearch
}

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''
