TEMPLATE = app
TEMPLATE = lib
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/e8yesearch.cpp \
    src/textquery.cpp \
    src/itextsearch.cpp \
    src/iqueryparser.cpp \
    src/idatasource.cpp \
    src/ispider.cpp \
    src/idatagatherer.cpp \
    src/e8yesgatherer.cpp \
    src/datasourceprimitive.cpp \
    src/document.cpp \
    src/term.cpp \
    src/spidy.cpp

LIBS += -lcppcms -lbooster
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lboost_system-mt -lboost_filesystem-mt

HEADERS += \
    src/e8yesearch.h \
    src/textquery.h \
    src/itextsearch.h \
    src/iqueryparser.h \
    src/idatasource.h \
    src/ispider.h \
    src/idatagatherer.h \
    src/e8yesgatherer.h \
    src/datasourceprimitive.h \
    src/document.h \
    src/term.h \
    src/spidy.h
