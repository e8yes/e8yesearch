TEMPLATE = app
TEMPLATE = lib
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/textquery.cpp \
    src/itextsearch.cpp \
    src/iqueryparser.cpp \
    src/idatasource.cpp \
    src/ispider.cpp \
    src/idatagatherer.cpp \
    src/e8yesgatherer.cpp \
    src/document.cpp \
    src/term.cpp \
    src/spidy.cpp \
    src/sqlitedatasource.cpp \
    src/utils.cpp \
    src/localdatagatherer.cpp \
    src/bptreedatasource.cpp \
    src/spidytextsearch.cpp \
    src/spidyqueryhandler.cpp \
    src/cpphtml/result.cpp \
    src/app.cpp \
    src/appweb.cpp \
    src/ijsonserializable.cpp \
    src/ibagofwords.cpp

LIBS += -lcppcms -lbooster
LIBS += -lxerces-c
LIBS += -lcppdb

macx {
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lboost_system-mt -lboost_filesystem-mt
}

unix:!macx {
LIBS += -lboost_system -lboost_filesystem
}

HEADERS += \
    src/textquery.h \
    src/itextsearch.h \
    src/iqueryparser.h \
    src/idatasource.h \
    src/ispider.h \
    src/idatagatherer.h \
    src/e8yesgatherer.h \
    src/document.h \
    src/term.h \
    src/spidy.h \
    src/sqlitedatasource.h \
    src/utils.h \
    src/localdatagatherer.h \
    src/bptreedatasource.h \
    src/mapbptree.h \
    src/spidytextsearch.h \
    src/spidyqueryhandler.h \
    src/cpphtml/result.h \
    src/app.h \
    src/appweb.h \
    src/ijsonserializable.h \
    src/ibagofwords.h

LIBS += -lcppcms -lbooster
LIBS += -lxerces-c
LIBS += -lcppdb
LIBS += -ljson

macx {
        INCLUDEPATH += /usr/local/include
        LIBS += -L/usr/local/lib
        LIBS += -lboost_system-mt -lboost_filesystem-mt
}

unix:!macx {
        LIBS += -lboost_system -lboost_filesystem
}
