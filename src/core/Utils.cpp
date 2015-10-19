#include "Utils.h"

#include "DialogGetItem.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/localities/LocalitiesTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "tables/milk_reception/MilkReceptionTable.h"
// qt
#include <QMessageBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QIcon>
#include <QAbstractItemView>
#include <QComboBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>


bool Utils::Main::isAutoIncrIdIsValid(const qlonglong id)
{
    return id > 0;
}

bool Utils::Main::yesNoWarnMsgBox(QWidget *parent, const QString &question)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(parent, Constants::appName(), question,
                                 QMessageBox::Yes|QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

bool Utils::Main::showWarnMsgIfNoRows(QWidget *parent, const QString &title, Table *table)
{
    if (table->isEmpty())
    {
        QMessageBox::warning(parent, Constants::appName(), title);
        return true;
    }
    return false;
}

bool Utils::Main::isNeesAddItem(QWidget *parent, Table *table)
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

        if (Utils::Main::yesNoWarnMsgBox(parent, title + QObject::tr("Желаете добавить сейчас?")))
            return true;
    }

    return false;
}

qlonglong Utils::Main::getIdFromDialog(Table *table, const QString &title, QWidget *parent)
{
    DialogGeItem dialog(table, title, parent);

    if (dialog.exec() == QDialog::Accepted)
        return dialog.getId();

    return -1;
}

QModelIndex Utils::Main::getIndexFromModelById(Table *table, const int column, const qlonglong id)
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

QVariant Utils::Main::getCurValueFromComboBoxModel(const QComboBox *combobox, const int column)
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

QVariant Utils::Main::getCurValueFromItemViewModel(const QAbstractItemView *itemView, const int column)
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

QString Utils::Main::getSelectStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "SELECT ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + ", ");

    return queryStr.replace(queryStr.length() - 2, 2, " FROM " + tableName);
}

QString Utils::Main::getPrepUpdateStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "UPDATE " + tableName + " SET ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + " = ?, ");

    return queryStr.replace(queryStr.length() - 2, 2, " ");
}

QString Utils::Main::getPrepInsertStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "INSERT INTO " + tableName + " (", values = "VALUES (";

    for(const auto &columnName: columns) {
        queryStr.append(columnName + ", ");
        values.append("?, ");
    }

    queryStr.replace(queryStr.length() - 2, 2, ") ");
    values.replace(values.length() - 2, 2, ")");

    return queryStr + values;
}

void Utils::Main::showMsgIfDbNotChoosed(QWidget *parent)
{
    QMessageBox::critical(parent, Constants::appName(), QObject::tr("Выберите бд для дальнейшей работы"));
}
