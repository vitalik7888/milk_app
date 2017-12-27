TEMPLATE = lib
TARGET = milkdbplugin
QT += qml quick sql
CONFIG += plugin c++14 addmilktypes addmilkdb

uri = com.milk.db
DESTDIR = $$MILK_QUICK_DEST_PATH/$$replace(uri, \., $$QMAKE_DIR_SEP)
TARGET = $$qtLibraryTarget($$TARGET)

# Input
include(include/headers.pri)

SOURCES += \
    src/db_plugin.cpp

OTHER_FILES += qmldir
DISTFILES = qmldir

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

CONFIG += install_ok  # Do not cargo-cult this!

