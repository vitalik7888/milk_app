#ifndef MILKPOINTDATA_H
#define MILKPOINTDATA_H

#include "IMilkPoint.h"
// Qt
#include <QString>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT MilkPointData : public IMilkPoint
{
public:
    MilkPointData();
    MilkPointData(const MilkPointData &mp);
    MilkPointData(const int id, const int localityId, const QString &name, const QString &description);
    MilkPointData &operator =(const MilkPointData &data);

    virtual int id() const Q_DECL_OVERRIDE;
    virtual void setId(const int id) Q_DECL_OVERRIDE;
    virtual QString name() const Q_DECL_OVERRIDE;
    virtual void setName(const QString &name) Q_DECL_OVERRIDE;
    virtual QString description() const Q_DECL_OVERRIDE;
    virtual void setDescription(const QString &description) Q_DECL_OVERRIDE;
    virtual int localityId() const Q_DECL_OVERRIDE;
    virtual void setLocalityId(const int localityId) Q_DECL_OVERRIDE;
    virtual bool isValid() const Q_DECL_OVERRIDE;

private:
    int m_id;
    int m_localityId;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(MilkPointData)

#endif // MILKPOINTDATA_H
