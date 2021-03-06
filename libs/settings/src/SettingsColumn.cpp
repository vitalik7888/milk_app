#include "SettingsColumn.h"

#include "SettingsConstants.h"

using SC = SettingsConstants;


SettingsColumn::SettingsColumn(QObject *parent):
    QObject(parent),
    m_display(SC::COL_DEF_DISPLAY),
    m_type(SC::COL_DEF_TYPE),
    m_prec(SC::COL_DEF_PREC),
    m_isShow(SC::COL_DEF_IS_SHOW)
{

}

SettingsColumn::SettingsColumn(const QString display, const int type,
                               const int prec, bool isShow, QObject *parent):
    QObject(parent),
    m_display(display),
    m_type(type),
    m_prec(prec),
    m_isShow(isShow)
{

}

SettingsColumn::~SettingsColumn() {}

void SettingsColumn::setDisplay(const QString &display)
{
    if (m_display == display)
        return;

    m_display = display;
    emit displayChanged(m_display);
}

void SettingsColumn::setType(const int type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void SettingsColumn::setPrec(const int prec)
{
    if (m_prec == prec)
        return;

    m_prec = prec;
    emit precChanged(m_prec);
}

void SettingsColumn::setIsShow(const bool isShow)
{
    if (m_isShow == isShow)
        return;

    m_isShow = isShow;
    emit isShowChanged(m_isShow);
}

void SettingsColumn::reset()
{
    resetDisplay();
    resetType();
    resetPrec();
    resetIsShow();
}

void SettingsColumn::resetDisplay()
{
    m_display = SC::COL_DEF_DISPLAY;
}

void SettingsColumn::resetType()
{
    m_type = SC::COL_DEF_TYPE;
}

void SettingsColumn::resetPrec()
{
    m_prec = SC::COL_DEF_PREC;
}

void SettingsColumn::resetIsShow()
{
    m_isShow = SC::COL_DEF_IS_SHOW;
}
