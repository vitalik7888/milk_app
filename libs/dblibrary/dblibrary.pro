#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T20:32:26
#
#-------------------------------------------------

QT       += qml sql gui

TARGET = dblibrary
TEMPLATE = lib

DEFINES += DBLIBRARY_LIBRARY

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        dblibrary_global.h 
include(db.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

for(var, $$list(settingslibrary typeslibrary)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../$$var/release/ -l$$var
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../$$var/debug/ -l$$var
    else:unix: LIBS += -L$$OUT_PWD/../$$var/ -l$$var

    INCLUDEPATH += $$PWD/../$$var
    DEPENDPATH += $$PWD/../$$var
}
