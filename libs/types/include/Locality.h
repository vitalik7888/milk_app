#ifndef _LOCALITY_H_
#define _LOCALITY_H_

#include "LocalityData.h"


class TYPESLIBRARYSHARED_EXPORT Locality : public MilkBaseItem
{
public:
    Locality();
    Locality(const MILK_ID id, const QString &name, const QString &description);
    Locality(const Locality &other);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_data->milkId(); }
    void setMilkId(const MILK_ID id) Q_DECL_OVERRIDE;

    QString name() const { return m_data->name(); }
    void setName(const QString &name);

    QString description() const { return m_data->description(); }
    void setDescription(const QString &description);

    bool isValid() const Q_DECL_OVERRIDE { return m_data->isValid(); }
    void reset() Q_DECL_OVERRIDE { m_data->reset(); }

private:
    QSharedDataPointer<LocalityData> m_data;
};

Q_DECLARE_METATYPE(Locality)

#endif
