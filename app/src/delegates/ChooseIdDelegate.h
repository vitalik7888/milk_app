#ifndef CHOOSEIDDELEGATE_H
#define CHOOSEIDDELEGATE_H

#include "dbconstants.h"
// Qt
#include <QItemDelegate>

DB_BEGIN_NAMESPACE
    class Table;
DB_END_NAMESPACE


class ChooseIdDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ChooseIdDelegate(DB_NAMESPACE::Table *table, const int idCol = -1,
                     const QString &title = QString(), QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    DB_NAMESPACE::Table *m_table;
    int m_colId;
    QString m_title;
};

#endif // CHOOSEIDDELEGATE_H
