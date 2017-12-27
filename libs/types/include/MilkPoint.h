#ifndef _MILKPOINT_H_
#define _MILKPOINT_H_

#include "MilkPointData.h"
// Qt
#include <QSharedDataPointer>

class Locality;


class TYPESLIBRARYSHARED_EXPORT MilkPoint : public MilkBaseItem
{
public:
    MilkPoint();
    MilkPoint(const MILK_ID id, const QString &name, const QString &description,
              const Locality *locality = Q_NULLPTR);
    MilkPoint(const MilkPoint &other);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_data->milkId(); }
    void setMilkId(const MILK_ID milkId) Q_DECL_OVERRIDE;

    const Locality *locality() const { return m_locality; }
    void setLocality(const Locality *locality);

    QString name() const { return m_data->name(); }
    void setName(const QString &name);

    QString description() const { return m_data->description(); }
    void setDescription(const QString &description);

    virtual bool isValid() const Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;

private:
    QSharedDataPointer<MilkPointData> m_data;
    const Locality *m_locality;
};

Q_DECLARE_METATYPE(MilkPoint)

#endif // MILKPOINT_H
