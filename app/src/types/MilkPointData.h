#ifndef MILKPOINTDATA_H
#define MILKPOINTDATA_H

// Qt
#include <QString>
#include <QMetaType>


class MilkPointData
{
public:
    MilkPointData();
    MilkPointData(const MilkPointData &mp);
    MilkPointData(const int id, const int localityId, const QString &name, const QString &description);

    MilkPointData &operator =(const MilkPointData &data);

    int id() const;
    void setId(const int id);

    int localityId() const;
    void setLocalityId(const int localityId);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    int m_id;
    int m_localityId;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(MilkPointData)

#endif // MILKPOINTDATA_H
