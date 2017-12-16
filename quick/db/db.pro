TEMPLATE = lib
TARGET = milkdbplugin
QT += qml quick sql
CONFIG += plugin c++14

uri = com.milk.db
DESTDIR = $$OUT_PWD/../../app/$$replace(uri, \., $$QMAKE_DIR_SEP)
TARGET = $$qtLibraryTarget($$TARGET)

# Input
SOURCES += \
    src/qmldb_plugin.cpp

include(include/headers.pri)

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

for(var, $$list(db types)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/$${var}/release/ -l$${var}library
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/$${var}/debug/ -l$${var}library
    else:unix: LIBS += -L$$OUT_PWD/../../libs/$${var}/ -l$${var}library

    INCLUDEPATH += $$PWD/../../libs/$${var}/include
    DEPENDPATH += $$PWD/../../libs/$${var}
}

CONFIG += install_ok  # Do not cargo-cult this!
