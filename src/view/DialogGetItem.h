#ifndef DIALOG_GET_ITEM_H
#define DIALOG_GET_ITEM_H

#include "dbconstants.h"
// Qt
#include <QDialog>

namespace Ui {
class DialogGetId;
}
class QSortFilterProxyModel;
DB_BEGIN_NAMESPACE
    class Table;
    class LocalitiesTable;
    class DeliverersTable;
    class MilkPointsTable;
DB_END_NAMESPACE


class DialogGeItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGeItem(DB_NAMESPACE::Table *table, const QString &title = QString(),
                          QWidget *parent = Q_NULLPTR);
    ~DialogGeItem();

    DB_NAMESPACE::Table *getTable() const;

    QModelIndex getIdModelIndex() const;

    void setCurrentItemById(const milk_id _id); // TODO
    void setCurrentItem(const QModelIndex &index); // TODO

    QString value() const;
    milk_id getId() const;

    bool getIsItemChoosed() const;

public slots:
    void accept() Q_DECL_OVERRIDE;
    void reject() Q_DECL_OVERRIDE;

    void refresh();
    void showInfo();

private:
    Ui::DialogGetId *ui;

    QSortFilterProxyModel *m_proxyModel;
    DB_NAMESPACE::LocalitiesTable *m_localities;
    DB_NAMESPACE::DeliverersTable *m_deliverers;
    DB_NAMESPACE::MilkPointsTable *m_milkPoints;

    bool m_isItemChoosed; // необходима, т. к. в не случаях exec нельзя проверить result()

private slots:
    void searchEnableCaseSensitivity(const bool isEnabled);
};

#endif // DIALOG_GET_ITEM_H
