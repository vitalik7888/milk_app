#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T15:18:25
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG  += plugin
QT      += qml quick sql

DESTDIR = ../../app/com/milk/db
TARGET = $$qtLibraryTarget(qmldbplugin)

SOURCES += \
        QmlDbPlugin.cpp

HEADERS += \
        QmlDbPlugin.h

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
    db.files = $$OUT_PWD/com/milk/db
    db.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += db
}

for(var, $$list(dblibrary settingslibrary typeslibrary)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/$$var/release/ -l$$var
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/$$var/debug/ -l$$var
    else:unix: LIBS += -L$$OUT_PWD/../../libs/$$var/ -l$$var

    INCLUDEPATH += $$PWD/../../libs/$$var
    DEPENDPATH += $$PWD/../../libs/$$var
}
