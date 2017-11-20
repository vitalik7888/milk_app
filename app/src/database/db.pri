INCLUDEPATH += $$PWD
SOURCES += \
    $$PWD/base/Database.cpp \
    $$PWD/base/Table.cpp \
    $$PWD/tables/deliverers/DeliverersTable.cpp \
    $$PWD/tables/localities/LocalitiesTable.cpp \
    $$PWD/tables/milk_points/MilkPointsTable.cpp \
    $$PWD/tables/milk_reception/MilkReceptionTable.cpp \
    $$PWD/tables/deliverers/DeliverersSortFilterProxyModel.cpp \
    $$PWD/tables/localities/LocalitiesSortFilterProxyModel.cpp \
    $$PWD/tables/milk_points/MilkPointsSortFilterProxyModel.cpp \
    $$PWD/DbUtils.cpp \
    $$PWD/base/Dao.cpp \
    $$PWD/DbConstants.cpp

HEADERS  += \
    $$PWD/base/Database.h \
    $$PWD/base/Table.h \
    $$PWD/tables/milk_reception/MilkReceptionTable.h \
    $$PWD/tables/deliverers/DeliverersTable.h \
    $$PWD/tables/localities/LocalitiesTable.h \
    $$PWD/tables/milk_points/MilkPointsTable.h \
    $$PWD/tables/deliverers/DeliverersSortFilterProxyModel.h \
    $$PWD/tables/localities/LocalitiesSortFilterProxyModel.h \
    $$PWD/tables/milk_points/MilkPointsSortFilterProxyModel.h \
    $$PWD/DbUtils.h \
    $$PWD/base/Dao.h \
    $$PWD/tables/deliverers/DeliverersDao.h \
    $$PWD/tables/localities/LocalitiesDao.h \
    $$PWD/tables/milk_points/MilkpointsDao.h \
    $$PWD/tables/milk_reception/MilkReceprionDao.h \
    $$PWD/DbConstants.h
