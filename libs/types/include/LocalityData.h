#ifndef LOCALITYDATA_H
#define LOCALITYDATA_H

#include "ILocality.h"
// Qt
#include <QString>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT LocalityData : public ILocality
{
public:
    LocalityData();
    LocalityData(const int id, const QString &name, const QString &description);
    LocalityData(const LocalityData &data);
    ~LocalityData();

    int id() const Q_DECL_OVERRIDE;
    void setId(const int id) Q_DECL_OVERRIDE;

    QString name() const Q_DECL_OVERRIDE;
    void setName(const QString &name) Q_DECL_OVERRIDE;

    QString description() const Q_DECL_OVERRIDE;
    void setDescription(const QString &description) Q_DECL_OVERRIDE;

    bool isValid() const Q_DECL_OVERRIDE;

private:
    int m_id;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(LocalityData)

#endif // LOCALITYDATA_H
