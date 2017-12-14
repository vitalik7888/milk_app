#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T15:18:25
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG  += plugin
QT      += qml quick sql

DESTDIR = ../../app/com/milk/calc
TARGET = $$qtLibraryTarget(qmlcalcplugin)

SOURCES += \
    QmlCalcPlugin.cpp

HEADERS += \
    QmlCalcPlugin.h

DESTPATH=$$OUT_PWD
target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

CONFIG += install_ok  # Do not cargo-cult this!
CONFIG += c++14

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR
COPIES += cpqmldir

osx {
    calc.files = $$OUT_PWD/com/milk/calc
    calc.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += calc
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/calclibrary/release/ -lcalclibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/calclibrary/debug/ -lcalclibrary
else:unix: LIBS += -L$$OUT_PWD/../../libs/calclibrary/ -lcalclibrary

INCLUDEPATH += $$PWD/../../libs/calclibrary
DEPENDPATH += $$PWD/../../libs/calclibrary
