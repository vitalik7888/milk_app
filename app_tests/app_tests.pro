QT += sql qml quick testlib
QT  -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14 qt warn_on depend_includepath testcase

TEMPLATE = app

include(../app/src/types/types.pri)
include(../app/src/calc/calc.pri)
include(../app/src/database/db.pri)

SOURCES += \ 
    main.cpp \
    settings/Test_MainSettings.cpp \
    settings/Test_CalcSettings.cpp \
    settings/Test_SettingsColumn.cpp \
    settings/Test_PrintSettings.cpp \
    settings/Test_Settings.cpp \
    types/Test_Deliverer.cpp \
    types/Test_Locality.cpp \
    types/Test_MilkPoint.cpp \
    types/Test_MilkReception.cpp \
    calc/Test_CalcUtils.cpp \
    db/Test_LocalitiesTable.cpp \
    types/Test_DelivererData.cpp \
    types/Test_LocalityData.cpp \
    types/Test_MilkReceptionData.cpp \
    types/Test_MilkPointData.cpp \
    calc/Test_CalculatedItemData.cpp

HEADERS += \
    settings/Test_MainSettings.h \
    settings/Test_CalcSettings.h \
    settings/Test_SettingsColumn.h \
    settings/Test_PrintSettings.h \
    settings/Test_Settings.h \
    types/Test_Deliverer.h \
    types/Test_Locality.h \
    types/Test_MilkPoint.h \
    types/Test_MilkReception.h \
    calc/Test_CalcUtils.h \
    db/Test_LocalitiesTable.h \
    types/Test_DelivererData.h \
    types/Test_LocalityData.h \
    types/Test_MilkReceptionData.h \
    types/Test_MilkPointData.h \
    calc/Test_CalculatedItemData.h

for(var, $$list(settingslibrary)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libraries/$$var/release/ -l$$var
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libraries/$$var/debug/ -l$$var
    else:unix: LIBS += -L$$OUT_PWD/../libraries/$$var/ -l$$var

    INCLUDEPATH += $$PWD/../libraries/$$var
    DEPENDPATH += $$PWD/../libraries/$$var
}
