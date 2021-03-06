#-------------------------------------------------
#
# Project created by QtCreator 2015-09-17T21:30:14
#
#-------------------------------------------------

QT  += sql printsupport qml quick gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = milk
TEMPLATE = app
#RC_ICONS = cow.png
DESTDIR = $$MILK_APP_DEST_PATH

CONFIG += c++14
CONFIG += addmilksettings addmilktypes addmilkcalc addmilkdb addmilkhtmlbuilder

include(include/interfaces.pri)

HEADERS += \
    include/Constants.h \
    include/DbExporter.h \
    include/MilkCore.h \
    include/MilkPlugins.h \
    include/CalcExporter.h

SOURCES += src/main.cpp \
    src/DbExporter.cpp \
    src/MilkCore.cpp \
    src/MilkPlugins.cpp \
    src/CalcExporter.cpp

RESOURCES += \
    res.qrc \
    qml/qml.qrc

OTHER_FILES += milk.sh

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH = com/milk/

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

unix {
    milk_script.files = milk.sh
    milk_script.path = $$DESTDIR
    milk_scipt.command = $(COPY_FILE) milk_script.files milk_script.files
    INSTALLS += milk_script
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
