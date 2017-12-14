#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T15:18:25
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG  += plugin
QT      += qml quick

DESTDIR = ../../app/com/milk/settings
TARGET = $$qtLibraryTarget(qmlsettingsplugin)

SOURCES += \
        QmlSettingsPlugin.cpp

HEADERS += \
        QmlSettingsPlugin.h

DESTPATH=$$OUT_PWD
target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

CONFIG += install_ok  # Do not cargo-cult this!

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR
COPIES += cpqmldir

osx {
    settings.files = $$OUT_PWD/com/milk/settings
    settings.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += settings
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libraries/settingslibrary/release/ -lsettingslibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libraries/settingslibrary/debug/ -lsettingslibrary
else:unix: LIBS += -L$$OUT_PWD/../../libraries/settingslibrary/ -lsettingslibrary

INCLUDEPATH += $$PWD/../../libraries/settingslibrary
DEPENDPATH += $$PWD/../../libraries/settingslibrary
