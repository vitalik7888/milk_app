#include "TypesConstants.h"

using TC = TypesConstants;
using TCD = TC::Deliverers;
using TCL = TC::Localities;
using TCMP = TC::MilkPoints;
using TCMR = TC::MilkReception;


const MILK_ID       TC::DEFAULT_ID = -1;

const QString       TCD::DEF_FIRST_NAME = {};
const QString       TCD::DEF_LAST_NAME = {};
const QString       TCD::DEF_INN = "";
const QString       TCD::DEF_ADDRESS = {};
const QString       TCD::DEF_PHONE_NUMBER = "";


const QString       TCL::DEF_NAME = "";
const QString       TCL::DEF_DESCRIPTION = "";

const QString       TCMP::DEF_NAME = "";
const QString       TCMP::DEF_DESCRIPTION = "";

const QString       TCMR::DEF_DELIVERER_NAME = "";
const QString       TCMR::DEF_MILK_POINT_NAME = "";
const QDate         TCMR::DEF_DELIVERY_DATE = {};
const double        TCMR::DEF_PRICE_LITER = .0;
const double        TCMR::DEF_LITERS = .0;
const double        TCMR::DEF_FAT = .0;
