#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T20:32:26
#
#-------------------------------------------------

QT       += qml sql

TARGET = dblibrary
TEMPLATE = lib

DEFINES += DBLIBRARY_LIBRARY
CONFIG += c++14 create_prl addmilktypes addmilksettings
DESTDIR = $$MILK_LIBS_DEST_PATH

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(include/headers.pri)

SOURCES += \
    src/Dao.cpp \
    src/Database.cpp \
    src/DbConstants.cpp \
    src/DbUtils.cpp \
    src/DeliverersSortFilterProxyModel.cpp \
    src/DeliverersTable.cpp \
    src/LocalitiesSortFilterProxyModel.cpp \
    src/LocalitiesTable.cpp \
    src/MilkPointsSortFilterProxyModel.cpp \
    src/MilkPointsTable.cpp \
    src/MilkReceptionSortFilterProxyModel.cpp \
    src/MilkReceptionTable.cpp \
    src/MilkSortFilterProxyModel.cpp \
    src/Table.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
