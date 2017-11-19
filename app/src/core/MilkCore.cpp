#include "MilkCore.h"

USE_DB_NAMESPACE

using SC = SettingsConstants;
using SCC = SettingsConstants::Column;
using COLTYPE = SC::SettingsColumnType;


MilkCore::MilkCore() :
    m_settings(new Settings()),
    m_database(new Database())
{
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

Settings *MilkCore::settings() const { return m_settings.data(); }

Database *MilkCore::database() const { return m_database.data(); }
