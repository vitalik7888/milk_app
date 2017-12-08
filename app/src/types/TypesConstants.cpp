#include "TypesConstants.h"

using TC = TypesConstants;
using TCD = TC::Deliverers;
using TCL = TC::Localities;
using TCMP = TC::MilkPoints;
using TCMR = TC::MilkReception;


const int           TCD::DEF_ID = -1;
const QString       TCD::DEF_NAME = {};
const int           TCD::DEF_LOCALITY_ID = -1;
const QString       TCD::DEF_INN = "";
const QString       TCD::DEF_ADDRESS = {};
const QString       TCD::DEF_PHONE_NUMBER = "";


const int           TCL::DEF_ID = -1;
const QString       TCL::DEF_NAME = "";
const QString       TCL::DEF_DESCRIPTION = "";

const int           TCMP::DEF_ID = -1;
const int           TCMP::DEF_LOCALITY_ID = -1;
const QString       TCMP::DEF_NAME = "";
const QString       TCMP::DEF_DESCRIPTION = "";

const int           TCMR::DEF_ID = -1;
const int           TCMR::DEF_ID_DELIVERER = -1;
const QString       TCMR::DEF_DELIVERER_NAME = "";
const int           TCMR::DEF_MILK_POINT_ID = -1;
const QString       TCMR::DEF_MILK_POINT_NAME = "";
const QDate         TCMR::DEF_DELIVERY_DATE = {};
const double        TCMR::M_DEF_PRICE_LITER = .0;
const double        TCMR::DEF_LITERS = .0;
const double        TCMR::DEF_FAT = .0;
