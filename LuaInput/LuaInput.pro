CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(luatextinputplugin)
TEMPLATE    = lib

HEADERS     = luatextinputplugin.h
SOURCES     = luatextinputplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(luatextinput.pri)

QT += widgets

DISTFILES +=

FORMS +=
