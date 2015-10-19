#-------------------------------------------------
#
# Project created by QtCreator 2015-09-17T21:30:14
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = milk
TEMPLATE = app

CONFIG += c++11

include(src/database/db.pri)
include(src/core/core.pri)
include(src/delegates/delegates.pri)

SOURCES += src/main.cpp

RESOURCES += \
    res.qrc
