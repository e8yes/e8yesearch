TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/e8yesearch.cpp \
    src/searchresult.cpp \
    src/textquery.cpp \
    src/itextsearch.cpp \
    src/iqueryparser.cpp \
    src/idatasource.cpp \
    src/ispider.cpp \
    src/idatagatherer.cpp \
    src/e8yesgatherer.cpp

LIBS += -lcppcms -lbooster

HEADERS += \
    src/e8yesearch.h \
    src/searchresult.h \
    src/textquery.h \
    src/itextsearch.h \
    src/iqueryparser.h \
    src/idatasource.h \
    src/ispider.h \
    src/idatagatherer.h \
    src/e8yesgatherer.h
