#include "TypesConstants.h"

using TC = TypesConstants;
using TCD = TC::Deliverers;
using TCL = TC::Localities;
using TCMP = TC::MilkPoints;
using TCMR = TC::MilkReception;


const TC::milk_id   TCD::DEF_ID = -1;
const QString       TCD::DEF_NAME = {};
const TC::milk_id   TCD::DEF_LOCALITY_ID = -1;
const TC::milk_inn  TCD::DEF_INN = -1;
const QString       TCD::DEF_ADDRESS = {};
const QString       TCD::DEF_PHONE_NUMBER = "";


const TC::milk_id   TCL::DEF_ID = -1;
const QString       TCL::DEF_NAME = "";
const QString       TCL::DEF_DESCRIPTION = "";

const TC::milk_id   TCMP::DEF_ID = -1;
const TC::milk_id   TCMP::DEF_LOCALITY_ID = -1;
const QString       TCMP::DEF_NAME = "";
const QString       TCMP::DEF_DESCRIPTION = "";

const TC::milk_id   TCMR::DEF_ID = -1;
const TC::milk_id   TCMR::DEF_ID_DELIVERER = -1;
const QString       TCMR::DEF_DELIVERER_NAME = "";
const TC::milk_id   TCMR::DEF_MILK_POINT_ID = -1;
const QString       TCMR::DEF_MILK_POINT_NAME = "";
const QDate         TCMR::DEF_DELIVERY_DATE = {};
const double        TCMR::DEF_PRICE_LITER = .0;
const double        TCMR::DEF_LITERS = .0;
const double        TCMR::DEF_FAT = .0;
