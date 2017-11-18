QT += core qml quick testlib
QT  -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14 qt warn_on depend_includepath testcase

TEMPLATE = app

include(../app/src/settings/settings.pri)

SOURCES += \ 
    main.cpp \
    Test_MainSettings.cpp \
    Test_CalcSettings.cpp \
    Test_SettingsColumn.cpp \
    Test_PrintSettings.cpp

HEADERS += \
    Test_MainSettings.h \
    Test_CalcSettings.h \
    Test_SettingsColumn.h \
    Test_PrintSettings.h
