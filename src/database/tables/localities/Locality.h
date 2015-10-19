#ifndef LOCALITY_H
#define LOCALITY_H

#include <QString>


class Locality {
public:
    Locality();
    Locality(const QString &name, const QString &description = "", const qlonglong id = -1);

    qlonglong id() const;
    void setId(const qlonglong &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isNull() const;

    QString toString() const;

    static Locality CREATE_NULL();

private:
    qlonglong _id;
    QString _name;
    QString _description;
};

#endif // LOCALITY_H
