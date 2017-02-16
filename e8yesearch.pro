TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/e8yesearch.cpp

LIBS += -lcppcms -lbooster

HEADERS += \
    src/e8yesearch.h
