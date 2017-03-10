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

unix:!macx {
LIBS += -L$$PWD/../build -le8yesearch
}

macx {
LIBS += -L../build-e8yesearch -le8yesearch
}

macx {
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lboost_system-mt -lboost_filesystem-mt
}

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''
