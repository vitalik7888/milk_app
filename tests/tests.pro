QT += sql qml quick testlib
QT  -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14 qt warn_on depend_includepath testcase

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
    src/db/Test_LocalitiesTable.cpp \
    src/types/Test_DelivererData.cpp \
    src/types/Test_LocalityData.cpp \
    src/types/Test_MilkReceptionData.cpp \
    src/types/Test_MilkPointData.cpp \
    src/calc/Test_CalculatedItemData.cpp

include(include/headers.pri)

LIBS_PATH = $$OUT_PWD/../app/libs
for(var, $$list(settings types calc db htmlbuilder)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$LIBS_PATH/ -l$${var}library
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$LIBS_PATH/ -l$${var}library
    else:unix: LIBS += -L$$LIBS_PATH/ -l$${var}library

    INCLUDEPATH += $$PWD/../libs/$${var}/include
    DEPENDPATH += $$PWD/../libs/$${var}
}
