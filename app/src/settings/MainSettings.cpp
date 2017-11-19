#include "MainSettings.h"

#include "SettingsConstants.h"

using SC = SettingsConstants;


MainSettings::MainSettings(const QString &lastChoosenDb, const float priceLiter, const QString &firmName,
                           const QString &milkInspector, const QString &milkInspector2,
                           const bool isFetchTablesOnRefresh, QObject *parent) :
    QObject(parent),
    m_lastChoosenDb(lastChoosenDb),
    m_priceLiter(priceLiter),
    m_firmName(firmName),
    m_milkInspector(milkInspector),
    m_milkInspector2(milkInspector2),
    m_isFetchTablesOnRefresh(isFetchTablesOnRefresh)
{

}

MainSettings::MainSettings(QObject *parent):
    MainSettings(SC::Main::DEF_LAST_CHOOSEN_DB,
                 SC::Main::DEF_PRICE_LITER,
                 SC::Main::DEF_FIRM_NAME,
                 SC::Main::DEF_MILK_INSPECTOR,
                 SC::Main::DEF_MILK_INSPECTOR2,
                 SC::Main::DEF_IS_FETCH_TABLE_ON_REFRESH,
                 parent)
{

}

MainSettings::~MainSettings()
{
}

void MainSettings::setLastChoosenDb(const QString &lastChoosenDb)
{
    if (m_lastChoosenDb == lastChoosenDb)
        return;

    m_lastChoosenDb = lastChoosenDb;
    emit lastChoosenDbChanged(m_lastChoosenDb);
}

void MainSettings::setPriceLiter(float priceLiter)
{
//    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_priceLiter, priceLiter))
        return;

    m_priceLiter = priceLiter;
    emit priceLiterChanged(m_priceLiter);
}

void MainSettings::setFirmName(const QString &firmName)
{
    if (m_firmName == firmName)
        return;

    m_firmName = firmName;
    emit firmNameChanged(m_firmName);
}

void MainSettings::setMilkInspector(const QString &milkInspector)
{
    if (m_milkInspector == milkInspector)
        return;

    m_milkInspector = milkInspector;
    emit milkInspectorChanged(m_milkInspector);
}

void MainSettings::setMilkInspector2(const QString &milkInspector2)
{
    if (m_milkInspector2 == milkInspector2)
        return;

    m_milkInspector2 = milkInspector2;
    emit milkInspector2Changed(m_milkInspector2);
}

void MainSettings::setIsFetchTablesOnRefresh(bool isFetchTablesOnRefresh)
{
    if (m_isFetchTablesOnRefresh == isFetchTablesOnRefresh)
        return;

    m_isFetchTablesOnRefresh = isFetchTablesOnRefresh;
    emit isFetchTablesOnRefreshChanged(m_isFetchTablesOnRefresh);
}

void MainSettings::reset()
{
    resetLastChoosenDb();
    resetPriceLiter();
    resetFirmName();
    resetMilkInspector();
    resetMilkInspector2();
    resetFetchTablesOnRefresh();
}

void MainSettings::resetLastChoosenDb()
{
    m_lastChoosenDb = SC::Main::DEF_LAST_CHOOSEN_DB;
}

void MainSettings::resetPriceLiter()
{
    m_priceLiter = SC::Main::DEF_PRICE_LITER;
}

void MainSettings::resetFirmName()
{
    m_firmName = SC::Main::DEF_FIRM_NAME;
}

void MainSettings::resetMilkInspector()
{
    m_milkInspector = SC::Main::DEF_MILK_INSPECTOR;
}

void MainSettings::resetMilkInspector2()
{
    m_milkInspector2 = SC::Main::DEF_MILK_INSPECTOR2;
}

void MainSettings::resetFetchTablesOnRefresh()
{
    m_isFetchTablesOnRefresh = SC::Main::DEF_IS_FETCH_TABLE_ON_REFRESH;
}
