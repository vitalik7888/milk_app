#ifndef DATEEDITDELEGATE_H
#define DATEEDITDELEGATE_H

#include <QStyledItemDelegate>

class DateEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DateEditDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DATEEDITDELEGATE_H
