INCLUDEPATH += $$PWD
SOURCES += \
    $$PWD/base/Database.cpp \
    $$PWD/base/Table.cpp \
    $$PWD/tables/deliverers/DeliverersTable.cpp \
    $$PWD/tables/localities/LocalitiesTable.cpp \
    $$PWD/tables/milk_points/MilkPointsTable.cpp \
    $$PWD/tables/milk_reception/MilkReceptionTable.cpp \
    $$PWD/base/dao.cpp \
    $$PWD/tables/deliverers/DeliverersSortFilterProxyModel.cpp \
    $$PWD/tables/localities/LocalitiesSortFilterProxyModel.cpp \
    $$PWD/tables/milk_points/MilkPointsSortFilterProxyModel.cpp \
    $$PWD/dbconstants.cpp \
    $$PWD/DbUtils.cpp

HEADERS  += \
    $$PWD/dbconstants.h \
    $$PWD/base/Database.h \
    $$PWD/base/Table.h \
    $$PWD/tables/milk_reception/MilkReceptionTable.h \
    $$PWD/tables/deliverers/DeliverersTable.h \
    $$PWD/tables/localities/LocalitiesTable.h \
    $$PWD/tables/milk_points/MilkPointsTable.h \
    $$PWD/tables/deliverers/deliverersdao.h \
    $$PWD/base/dao.h \
    $$PWD/tables/localities/localitiesdao.h \
    $$PWD/tables/milk_points/milkpointdao.h \
    $$PWD/tables/milk_reception/milkrecepriondao.h \
    $$PWD/tables/deliverers/DeliverersSortFilterProxyModel.h \
    $$PWD/tables/localities/LocalitiesSortFilterProxyModel.h \
    $$PWD/tables/milk_points/MilkPointsSortFilterProxyModel.h \
    $$PWD/DbUtils.h
