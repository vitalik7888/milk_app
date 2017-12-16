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

CONFIG += c++14

include(include/interfaces.pri)

HEADERS += \
    include/Constants.h \
    include/DbExporter.h \
    include/MilkCore.h \
    include/MilkPlugins.h

SOURCES += src/main.cpp \
    src/DbExporter.cpp \
    src/MilkCore.cpp \
    src/MilkPlugins.cpp

RESOURCES += \
    res.qrc \
    qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH = com/milk

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

for(var, $$list(settings types calc db htmlbuilder)) {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/$${var}/release/ -l$${var}library
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/$${var}/debug/ -l$${var}library
    else:unix: LIBS += -L$$OUT_PWD/../libs/$${var}/ -l$${var}library

    INCLUDEPATH += $$PWD/../libs/$${var}/include
    DEPENDPATH += $$PWD/../libs/$${var}
}
