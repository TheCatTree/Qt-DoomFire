TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += C:\LUA\lua-5.3.5\include
LIBS += -LC:\LUA\lua\bin -llua53static
SOURCES += main.cpp \
    main.cpp
