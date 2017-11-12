#-------------------------------------------------
#
# Project created by QtCreator 2015-09-17T21:30:14
#
#-------------------------------------------------

QT  += core sql printsupport qml quick
QT  -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = milk
TEMPLATE = app
#RC_ICONS = cow.ico

CONFIG += c++14

include(src/database/db.pri)
include(src/types/types.pri)
include(src/settings/settings.pri)
include(src/core/core.pri)

SOURCES += src/main.cpp

RESOURCES += \
    res.qrc \
    src/qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
