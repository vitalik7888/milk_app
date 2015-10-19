#ifndef DIALOG_GET_ITEM_H
#define DIALOG_GET_ITEM_H

#include <QDialog>

namespace Ui {
class DialogGetId;
}
class QSortFilterProxyModel;
class Table;
class DeliverersTable;
class LocalitiesTable;
class MilkPointsTable;


class DialogGeItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGeItem(Table *table, const QString &title = QString(), QWidget *parent = 0);
    ~DialogGeItem();

    Table *getTable() const;

    QModelIndex getIdModelIndex() const;

    void setCurrentItemById(const qlonglong _id); // TODO
    void setCurrentItem(const QModelIndex &index); // TODO

    QString value() const;
    qlonglong getId() const;

    bool getIsItemChoosed() const;

public slots:
    void accept() Q_DECL_OVERRIDE;
    void reject() Q_DECL_OVERRIDE;

    void refresh();
    void showInfo();

private:
    Ui::DialogGetId *ui;

    QSortFilterProxyModel *m_proxyModel;
    LocalitiesTable *m_localities;
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;

    bool m_isItemChoosed; // необходима, т. к. в не случаях exec нельзя проверить result()

private slots:
    void searchEnableCaseSensitivity(const bool isEnabled);
};

#endif // DIALOG_GET_ITEM_H
