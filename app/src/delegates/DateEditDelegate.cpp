#include "DateEditDelegate.h"

#include <QDateEdit>

DateEditDelegate::DateEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *DateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    auto editor = new QDateEdit(parent);

    editor->setDisplayFormat("dd/MMMM/yy");
    editor->setCalendarPopup(true);
    editor->setDate(QDate::currentDate());

    return editor;
}

void DateEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto date = index.model()->data(index, Qt::EditRole).toDate();

    auto dateEdit = static_cast<QDateEdit*>(editor);
    dateEdit->setDate(date);
}

void DateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto dateEdit = static_cast<QDateEdit*>(editor);

    dateEdit->interpretText();

    auto date = dateEdit->date();

    model->setData(index, date, Qt::EditRole);
}

void DateEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
