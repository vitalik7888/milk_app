#ifndef MILKBASE_DB_OBJECT_H_
#define MILKBASE_DB_OBJECT_H_

#include "DbConstants.h"
#include "MilkModel.h"

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT MilkBaseDbObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MilkModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(MILK_ID milkId READ milkId WRITE setMilkId NOTIFY milkIdChanged)

public:
    explicit MilkBaseDbObject(QObject *parent = Q_NULLPTR);

    MILK_ID milkId() const { return m_item->milkId(); }

    MilkModel* model() const { return m_model; }

    Q_INVOKABLE bool isValid() const;
    Q_INVOKABLE int getPositionInModel() const;

signals:
    void milkIdChanged(const MILK_ID milkId);
    void modelChanged(MilkModel* model);
    void dataLoaded();

public slots:
    void setMilkId(const MILK_ID milkId);
    void setModel(MilkModel* model);
    virtual void setItem(const MilkBaseItem *item);
    void reset();
    bool loadData(const MILK_ID id);
    bool saveValue(const QVariant &value, const int role = Qt::EditRole);
    bool save();
    bool remove();
    bool append();

private:
    MilkModel* m_model;

protected:
    std::unique_ptr<MilkBaseItem> m_item;

    bool check() const;
};

DB_END_NAMESPACE

#endif // MILKBASEDBOBJECT_H
