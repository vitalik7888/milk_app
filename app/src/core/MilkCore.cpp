#include "MilkCore.h"

#include <DbUtils.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE

using SC = SettingsConstants;
using SCC = SettingsConstants::Column;
using COLTYPE = SC::SettingsColumnType;
using DBC = DbConstants;
using DBCMR = DBC::MilkReception;


MilkCore::MilkCore(QObject *parent) :
    QObject(parent)
{
    m_settings = new Settings();
    m_database = new Database();

    auto print = m_settings->print();
    print->setSettingsColumns(
    {
                    new SettingsColumn(QObject::tr("№ п/п"), COLTYPE::SerialNumber, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Ф. И. О."), COLTYPE::String, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Физ. вес"), COLTYPE::Double, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("% жир"), COLTYPE::Double, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Белок"), COLTYPE::Double, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Жироед."), COLTYPE::Double, SCC::DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Зачет. вес"), COLTYPE::Double, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Оплата(без премии)"), COLTYPE::Double, SCC::DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Премия"), COLTYPE::Double, SCC::DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Сумма"), COLTYPE::Double, SCC::DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Подпись"), COLTYPE::String, SCC::DEF_PREC, true, print)
                });
    auto calc = m_settings->calc();
    calc->setSettingsColumns(
    {
                    new SettingsColumn(QObject::tr("Ф. И. О."), COLTYPE::String, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Молокопункты"), COLTYPE::String, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Дата сдачи"), COLTYPE::Date, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Цена за литр"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Литры"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Жиры"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Белок"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Жироед."), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Зачет. вес"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Оплата(без премии)"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Премия"), COLTYPE::Double, SCC::DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Сумма"), COLTYPE::Double, SCC::DEF_PREC, true, calc)
                });
}

MilkCore::~MilkCore() {}

Settings *MilkCore::settings() const { return m_settings; }

Database *MilkCore::database() const { return m_database; }

CalculatedItem *MilkCore::getCalculations(const QString &where)
{
    auto root = new CalculatedItem;
    root->setDelivererName("All");

    QHash<DBC::milk_id, MilkPointData> milkPointsData;
    QHash<DBC::milk_id, CalculatedItem *> deliverersCi;

    auto getMilkPoint = [this, &milkPointsData](const DBC::milk_id id) -> MilkPointData {
        if (milkPointsData.contains(id))
            return milkPointsData[id];
        else {
            const auto mpdOptional = database()->milkPoints()->getMilkPointData(id);
            if (mpdOptional) {
                milkPointsData.insert(id, mpdOptional.value());
                return mpdOptional.value();
            }
        }
        return {};
    };

    auto getDelivererCi = [this, &deliverersCi](const DBC::milk_id id) -> CalculatedItem* {
        if (deliverersCi.contains(id))
            return deliverersCi[id];
        else {
            const auto delivererOptional = database()->deliverers()->getDelivererData(id);
            if (delivererOptional) {
                const auto delivererData = delivererOptional.value();

                auto delivererCi = new CalculatedItem;
                delivererCi->setDelivererName(delivererData.name());

                deliverersCi.insert(id, delivererCi);
                return delivererCi;
            }
        }

        return Q_NULLPTR;
    };

    const auto milkReceptions = database()->milkReception()->getMilkReceptionsData(where);
    for (const auto mr : milkReceptions) {
        auto delivererCi = getDelivererCi(mr.delivererId());

        const auto milkPointData = getMilkPoint(mr.milkPointId());

        auto milkReceptionCalcItem = new CalculatedItem(mr.liters(), mr.fat(), mr.priceLiter(), delivererCi);
        milkReceptionCalcItem->setDeliveryDate(mr.deliveryDate());
        milkReceptionCalcItem->setMilkPointName(milkPointData.name());

        delivererCi->addItem(milkReceptionCalcItem);
    }
    for (auto item : deliverersCi) {
        item->setParent(root);
        root->addItem(item);
    }

    return root;
}

CalcItemModel *MilkCore::getCalcItemModel(const qlonglong delivererId, const qlonglong milkPointId,
                                          const QDate &dateFrom, const QDate &dateTo)
{
    const auto delivererWhere = delivererId <= 0 ?
                "" : QString("%1 = %2")
                .arg(DBCMR::FN_ID_DELIVERER)
                .arg(delivererId);
    const auto milkPointWhere = milkPointId <= 0 ?
                "" : QString("%1 = %2")
                .arg((delivererWhere.isEmpty() ? "" : " AND ") + DBCMR::FN_MILK_POINT_ID)
                .arg(milkPointId);
    const auto dateWhere = !dateFrom.isValid() ?
                "" : QString("%1 BETWEEN %2 AND %3")
                .arg((milkPointWhere.isEmpty() ? "" : " AND ") + DBCMR::FN_DELIVERY_DATE)
                .arg(dateFrom.toString(SC::defaultDateFormat()))
                .arg(dateTo.toString(SC::defaultDateFormat()));

    auto model = new CalcItemModel(getCalculations(delivererWhere + milkPointWhere + dateWhere), this);
    model->setDateFormat(SC::defaultDateFormat());
    return model;
}

