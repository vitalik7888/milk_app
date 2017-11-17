#include "ComboBoxDelegate.h"

#include <QComboBox>


ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/,
                                        const QModelIndex &/*index*/) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(false);

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox*>(editor);

    comboBox->setCurrentIndex(comboBox->findText(value));
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(model);
    Q_UNUSED(index);

//    QComboBox *comboBox = static_cast<QComboBox *>(editor);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                            const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}
