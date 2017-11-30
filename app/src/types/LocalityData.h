#ifndef LOCALITYDATA_H
#define LOCALITYDATA_H

// Qt
#include <QString>
#include <QMetaType>


class LocalityData {
public:
    LocalityData();
    LocalityData(const int id, const QString &name, const QString &description);
    LocalityData(const LocalityData &data);
    ~LocalityData();

    int id() const;
    void setId(const int id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    int m_id;
    QString m_name;
    QString m_description;
};

Q_DECLARE_METATYPE(LocalityData)

#endif // LOCALITYDATA_H
