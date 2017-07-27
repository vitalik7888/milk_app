#include "ViewUtils.h"

#include "DialogGetItem.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/localities/LocalitiesTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "tables/milk_reception/MilkReceptionTable.h"
#include "src/core/Constants.h"
// Qt
#include <QMessageBox>
#include <QDialog>
#include <QAbstractItemView>
#include <QComboBox>

USE_DB_NAMESPACE


bool ViewUtils::yesNoWarnMsgBox(QWidget *parent, const QString &question)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(parent, Constants::appName(), question,
                                 QMessageBox::Yes|QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

bool ViewUtils::showWarnMsgIfNoRows(QWidget *parent, const QString &title, Table *table)
{
    if (table->isEmpty())
    {
        QMessageBox::warning(parent, Constants::appName(), title);
        return true;
    }
    return false;
}

bool ViewUtils::isNeesAddItem(QWidget *parent, Table *table)
{
    if (table->isEmpty()) {
        QString title = "";
        if (table->objectName() == "DeliverersTable")
            title = "Отсутствуют сдатчики. ";
        else if (table->objectName() == "LocalitiesTable")
            title = "Отсутствуют населенные пункты. ";
        else if (table->objectName() == "MilkPointsTable")
            title = "Отсутствуют молокопункты. ";
        else if (table->objectName() == "MilkReceptionTable")
            title = "Отсутствуют сдачи молока. ";

        if (ViewUtils::yesNoWarnMsgBox(parent, title + QObject::tr("Желаете добавить сейчас?")))
            return true;
    }

    return false;
}

milk_id ViewUtils::getIdFromDialog(Table *table, const QString &title, QWidget *parent)
{
    DialogGeItem dialog(table, title, parent);

    if (dialog.exec() == QDialog::Accepted)
        return dialog.getId();

    return -1;
}

QModelIndex ViewUtils::getIndexFromModelById(Table *table, const int column, const milk_id id)
{
    for (int row = 0; row < table->rowCount(); row++)
    {
        const auto index = table->index(row, column);
        if (index.isValid()) {
            if (index.data().toLongLong() == id)
                return index;
        }
    }
    return QModelIndex();
}

QVariant ViewUtils::getCurValueFromComboBoxModel(const QComboBox *combobox, const int column)
{
    const auto model = dynamic_cast<QSqlQueryModel *>(combobox->model());
    if (model)
    {
        const auto record = model->record(combobox->currentIndex());
        const auto field = record.field(column);
        return field.value();
    }

    return QVariant();
}

QVariant ViewUtils::getCurValueFromItemViewModel(const QAbstractItemView *itemView, const int column)
{
    const auto model = dynamic_cast<QSqlQueryModel *>(itemView->model());
    if (model)
    {
        const auto record = model->record(itemView->currentIndex().row());
        const auto field = record.field(column);
        return field.value();
    }

    return QVariant();
}

void ViewUtils::showMsgIfDbNotChoosed(QWidget *parent)
{
    QMessageBox::critical(parent, Constants::appName(), QObject::tr("Выберите бд для дальнейшей работы"));
}
