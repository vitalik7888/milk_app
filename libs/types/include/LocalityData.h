#ifndef LOCALITY_DATA_H_
#define LOCALITY_DATA_H_

#include "MilkBaseItem.h"
// Qt
#include <QSharedData>
#include <QMetaType>

class TYPESLIBRARYSHARED_EXPORT LocalityData : public MilkBaseItem, public QSharedData
{
public:
    LocalityData();
    LocalityData(const MILK_ID id, const QString &name, const QString &description);
    LocalityData(const LocalityData &data);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_milkId; }
    void setMilkId(const MILK_ID id) Q_DECL_OVERRIDE;

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    virtual void reset() Q_DECL_OVERRIDE;

private:
    MILK_ID m_milkId;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(LocalityData)

#endif // LOCALITYDATA_H
