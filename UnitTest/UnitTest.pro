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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-e8yesearch-Desktop_Qt_5_7_0_GCC_64bit-Debug/release/ -le8yesearch
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-e8yesearch-Desktop_Qt_5_7_0_GCC_64bit-Debug/debug/ -le8yesearch
else:unix: LIBS += -L$$PWD/../../build-e8yesearch-Desktop_Qt_5_7_0_GCC_64bit-Debug/ -le8yesearch

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''
