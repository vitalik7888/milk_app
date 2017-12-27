#ifndef MILKPOINT_DATA_H_
#define MILKPOINT_DATA_H_

#include "MilkBaseItem.h"
// Qt
#include <QSharedData>
#include <QMetaType>

class TYPESLIBRARYSHARED_EXPORT MilkPointData : public MilkBaseItem, public QSharedData
{
public:
    MilkPointData();
    MilkPointData(const MilkPointData &mp);
    MilkPointData(const MILK_ID id, const MILK_ID localityId, const QString &name, const QString &description);
    MilkPointData &operator =(const MilkPointData &data);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_milkId; }
    void setMilkId(const MILK_ID milkId) Q_DECL_OVERRIDE;

    MILK_ID localityId() const { return m_localityId; }
    void setLocalityId(const MILK_ID localityId);

    QString name() const { return m_name; }
    void setName(const QString &name);

    QString description() const { return m_description; }
    void setDescription(const QString &description);

    virtual bool isValid() const Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;

private:
    MILK_ID m_milkId;
    MILK_ID m_localityId;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(MilkPointData)

#endif // MILKPOINTDATA_H
