TEMPLATE = lib
TARGET = milktypesplugin
QT += qml quick
CONFIG += plugin c++14

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.milk.types
DESTDIR = ../../app/$$replace(uri, \., $$QMAKE_DIR_SEP)

# Input
include(include/headers.pri)

SOURCES += \
    src/types_plugin.cpp

DISTFILES = qmldir

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR
COPIES += cpqmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

LIBS_PATH = $$OUT_PWD/../../app/libs
win32:CONFIG(release, debug|release): LIBS += -L$$LIBS_PATH/ -ltypeslibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$LIBS_PATH/ -ltypeslibrary
else:unix: LIBS += -L$$LIBS_PATH/ -ltypeslibrary

INCLUDEPATH += $$PWD/../../libs/types/include
DEPENDPATH += $$PWD/../../libs/types

CONFIG += install_ok  # Do not cargo-cult this!
