TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    listener.cpp \
    listener2.cpp \
    sender.cpp \
    receiver.cpp

HEADERS += \
    listener.h \
    listener2.h \
    sender.h \
    receiver.h
