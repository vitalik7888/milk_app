#ifndef MILKPOINTSSORTFILTERPROXYMODEL_H
#define MILKPOINTSSORTFILTERPROXYMODEL_H

#include <QObject>

class MilkPointsSortFilterProxyModel : public QObject
{
    Q_OBJECT
public:
    explicit MilkPointsSortFilterProxyModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MILKPOINTSSORTFILTERPROXYMODEL_H