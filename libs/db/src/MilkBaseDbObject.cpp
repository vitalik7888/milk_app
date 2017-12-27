#include "MilkBaseDbObject.h"

#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using TC = TypesConstants;


MilkBaseDbObject::MilkBaseDbObject(QObject *parent) :
    QObject(parent),
    m_model(Q_NULLPTR),
    m_item(Q_NULLPTR)
{

}

bool MilkBaseDbObject::isValid() const
{
    return m_item->isValid();
}

int MilkBaseDbObject::getPositionInModel() const
{
    if (!m_model)
        return -1;

    return m_model->getPositionById(milkId());
}

void MilkBaseDbObject::setModel(MilkModel *table)
{
    if (m_model == table)
        return;

    m_model = table;
    m_item->reset();
    emit modelChanged(m_model);
}

void MilkBaseDbObject::setItem(const MilkBaseItem *item)
{
    setMilkId(item ? item->milkId() : TC::DEFAULT_ID);
}

void MilkBaseDbObject::reset()
{
    setItem(Q_NULLPTR);
}

bool MilkBaseDbObject::loadData(const MILK_ID id)
{
    if (!m_model) {
        qWarning() << "Model is null";
        return false;
    }

    if (id < 0) {
        qWarning() << "Invalid milk id";
        return false;
    }

    auto data = m_model->getItemById(id);
    if (data) {
        setItem(data);
        emit dataLoaded();
        return true;
    }

    return false;
}

bool MilkBaseDbObject::save()
{
    if (!check())
        return false;

    return m_model->update(m_item.get());
}

bool MilkBaseDbObject::remove()
{
    if (!check())
        return false;

    return m_model->removeById(milkId());
}

bool MilkBaseDbObject::append()
{
    if (!check())
        return false;

    return m_model->append(m_item.get());
}

bool MilkBaseDbObject::saveValue(const QVariant &value, const int role)
{
    bool isOk = m_model->setData(m_model->index(getPositionInModel()), value, role);
    if (isOk)
        loadData(milkId());

    return isOk;
}

void MilkBaseDbObject::setMilkId(const MILK_ID milkId)
{
    if (this->milkId() == milkId)
        return;

    m_item->setMilkId(milkId);
    emit milkIdChanged(milkId);
}

bool MilkBaseDbObject::check() const
{
    if (!m_model) {
        qWarning() << "Table is null";
        return false;
    }

    if (!m_item) {
        qWarning() << "Data is null";
        return false;
    }

    return true;
}
