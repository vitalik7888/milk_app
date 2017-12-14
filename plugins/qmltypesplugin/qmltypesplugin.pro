#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T15:18:25
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG  += plugin
QT      += qml quick sql

DESTDIR = ../../app/com/milk/types
TARGET = $$qtLibraryTarget(qmltypesplugin)

SOURCES += \
    QmlTypesPlugin.cpp

HEADERS += \
    QmlTypesPlugin.h

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
    types.files = $$OUT_PWD/com/milk/types
    types.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += types
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/typeslibrary/release/ -ltypeslibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/typeslibrary/debug/ -ltypeslibrary
else:unix: LIBS += -L$$OUT_PWD/../../libs/typeslibrary/ -ltypeslibrary

INCLUDEPATH += $$PWD/../../libs/typeslibrary
DEPENDPATH += $$PWD/../../libs/typeslibrary
