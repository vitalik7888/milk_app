INCLUDEPATH += $$PWD
SOURCES += \
    $$PWD/base/Database.cpp \
    $$PWD/base/Table.cpp \
    $$PWD/tables/deliverers/DeliverersTable.cpp \
    $$PWD/tables/localities/LocalitiesTable.cpp \
    $$PWD/tables/milk_points/MilkPointsTable.cpp \
    $$PWD/tables/milk_reception/MilkReceptionTable.cpp \
    $$PWD/tables/deliverers/delivererdata.cpp \
    $$PWD/tables/milk_reception/milkreceptiondata.cpp \
    $$PWD/tables/milk_points/milkpointdata.cpp \
    $$PWD/base/dao.cpp \
    $$PWD/tables/localities/localitydata.cpp

HEADERS  += \
    $$PWD/dbconstants.h \
    $$PWD/base/Database.h \
    $$PWD/base/Table.h \
    $$PWD/tables/milk_reception/MilkReceptionTable.h \
    $$PWD/tables/deliverers/DeliverersTable.h \
    $$PWD/tables/localities/LocalitiesTable.h \
    $$PWD/tables/milk_points/MilkPointsTable.h \
    $$PWD/tables/deliverers/delivererdata.h \
    $$PWD/tables/milk_points/milkpointdata.h \
    $$PWD/tables/milk_reception/milkreceptiondata.h \
    $$PWD/tables/deliverers/deliverersdao.h \
    $$PWD/base/dao.h \
    $$PWD/tables/localities/localitiesdao.h \
    $$PWD/tables/milk_points/milkpointdao.h \
    $$PWD/tables/milk_reception/milkrecepriondao.h \
    $$PWD/tables/localities/localitydata.h
