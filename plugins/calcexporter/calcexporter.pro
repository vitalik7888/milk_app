#-------------------------------------------------
#
# Project created by QtCreator 2018-01-15T14:28:10
#
#-------------------------------------------------

QT       += core qml

TARGET = calcexporter
TEMPLATE = lib
CONFIG += plugin
CONFIG += addmilktypes addmilkcalc

DESTDIR = $$MILK_PLUGS_DEST_PATH

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../app/include/interfaces.pri)
include(include/headers.pri)

SOURCES += \
    src/CalcExporterPlugin.cpp

DISTFILES += calcexporter.json 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += install_ok  # Do not cargo-cult this!
