QT += sql qml quick testlib
QT  -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14 qt warn_on depend_includepath testcase
CONFIG += addmilksettings addmilktypes addmilkcalc addmilkdb addmilkhtmlbuilder

TEMPLATE = app

SOURCES += \ 
    src/main.cpp \
    src/settings/Test_MainSettings.cpp \
    src/settings/Test_CalcSettings.cpp \
    src/settings/Test_SettingsColumn.cpp \
    src/settings/Test_PrintSettings.cpp \
    src/settings/Test_Settings.cpp \
    src/types/Test_Deliverer.cpp \
    src/types/Test_Locality.cpp \
    src/types/Test_MilkPoint.cpp \
    src/types/Test_MilkReception.cpp \
    src/calc/Test_CalcUtils.cpp \
    src/types/Test_DelivererData.cpp \
    src/types/Test_LocalityData.cpp \
    src/types/Test_MilkReceptionData.cpp \
    src/types/Test_MilkPointData.cpp \
    src/calc/Test_CalculatedItemData.cpp \
    src/db/Test_LocalitiesTable.cpp \
    src/db/Test_LocalitiesDao.cpp \
    src/db/DbTests.cpp

include(include/headers.pri)
