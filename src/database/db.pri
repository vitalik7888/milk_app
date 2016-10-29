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
    $$PWD/tables/deliverers/Deliverer.cpp \
    $$PWD/tables/localities/Locality.cpp \
    $$PWD/tables/milk_points/MilkPoint.cpp \
    $$PWD/tables/milk_reception/MilkReception.cpp

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
    $$PWD/tables/deliverers/Deliverer.h \
    $$PWD/tables/localities/Locality.h \
    $$PWD/tables/milk_points/MilkPoint.h \
    $$PWD/tables/milk_reception/MilkReception.h
