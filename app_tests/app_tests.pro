QT += core sql qml quick testlib
QT  -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14 qt warn_on depend_includepath testcase

TEMPLATE = app

include(../app/src/settings/settings.pri)
include(../app/src/types/types.pri)
#include(../app/src/database/db.pri)
#include(../app/src/calc/calc.pri)

SOURCES += \ 
    main.cpp \
    settings/Test_MainSettings.cpp \
    settings/Test_CalcSettings.cpp \
    settings/Test_SettingsColumn.cpp \
    settings/Test_PrintSettings.cpp \
    settings/Test_Settings.cpp \
    types/Test_Deliverer.cpp \
    types/Test_Locality.cpp

HEADERS += \
    settings/Test_MainSettings.h \
    settings/Test_CalcSettings.h \
    settings/Test_SettingsColumn.h \
    settings/Test_PrintSettings.h \
    settings/Test_Settings.h \
    types/Test_Deliverer.h \
    types/Test_Locality.h
