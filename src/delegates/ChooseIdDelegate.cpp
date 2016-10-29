#include "ChooseIdDelegate.h"

#include "tables/milk_reception/MilkReceptionTable.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "DialogGetItem.h"
#include "Utils.h"
// Qt
#include <QLabel>
#include  <QMessageBox>

USE_DB_NAMESPACE


ChooseIdDelegate::ChooseIdDelegate(Table *table, const int idCol, const QString &title, QObject *parent):
    QItemDelegate(parent),
    m_table(table),
    m_colId(idCol),
    m_title(title)
{
}

QWidget *ChooseIdDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new DialogGeItem(m_table, m_title, parent);
}

void ChooseIdDelegate::setEditorData(QWidget *_editor, const QModelIndex &_index) const
{
    const auto colId = m_colId == -1 ? _index.column() : m_colId;
    const auto _id = _index.model()->index(_index.row(), colId).data().toLongLong();

    auto editor = static_cast<DialogGeItem *>(_editor);
    editor->setCurrentItemById(_id);
}

void ChooseIdDelegate::setModelData(QWidget *_editor, QAbstractItemModel *_model, const QModelIndex &_index) const
{
    auto editor = static_cast<DialogGeItem *>(_editor);
    if (!editor->getIsItemChoosed())
        return;

    const auto _id = editor->getId();
    if (!Utils::Main::isAutoIncrIdIsValid(_id)) {
        QMessageBox::critical(_editor, Constants::appName(), tr("Не удалось установить значение"));
        return;
    }

    const auto colId = m_colId == -1 ? _index.column() : m_colId;
    _model->setData(_model->index(_index.row(), colId), _id, Qt::EditRole);
}

void ChooseIdDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
