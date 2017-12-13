#ifndef CALCITEMMODEL_H
#define CALCITEMMODEL_H

#include "CalculatedItem.h"
// Qt
#include <QAbstractItemModel>


class CalcItemModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString dateFormat READ dateFormat WRITE setDateFormat)
    Q_PROPERTY(int prec READ prec WRITE setPrec)
    Q_PROPERTY(CalculatedItem* calcItemRoot READ calcItemRoot CONSTANT)

public:
    CalcItemModel(QObject *parent = Q_NULLPTR);
    CalcItemModel(CalculatedItem *calcItem, QObject *parent = Q_NULLPTR);
    virtual ~CalcItemModel();

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    QString dateFormat() const { return m_dateFormat; }
    int prec() const { return m_prec; }

    CalculatedItem *calcItemRoot() const { return m_root->getItems().first(); }

public slots:
    void setDateFormat(const QString &dateFormat);
    void setPrec(int prec);

private:
    CalculatedItem *m_root;
    QString m_dateFormat;
    int m_prec;
};

#endif // CALCITEMMODEL_H
