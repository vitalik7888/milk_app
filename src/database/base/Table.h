#ifndef ABSTRACT_TABLE
#define ABSTRACT_TABLE

#include <QString>
#include <QVector>

#include <QSqlQueryModel>

#include <QSqlRecord>
#include <QSqlField>


class Table : public QSqlQueryModel
{
    Q_OBJECT
public:
    Table(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    virtual ~Table();

    QSqlDatabase database() const;

    virtual QString tableName() const = 0;
    virtual void initColumns() = 0;
    virtual QSqlField primaryField() const = 0;

    virtual QString selectAll() const;
    bool isEmpty() const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

    bool remove(const qlonglong id) const;
    bool removeAll() const;

    virtual void refresh();

    QSqlRecord getColumns() const;
    int getColumnsCount() const;

    int getColumnPosition(const QString &name) const;

    bool getIsFetchOnRefresh() const;
    void setIsFetchOnRefresh(const bool isFetchOnRefresh);

protected:
    QSqlDatabase m_db;

    /*!
     * \brief Столбцы таблицы
     */
    QSqlRecord m_columns;  /* вместо record(), т. к. необходимо описание столбцов
                до первоначального запроса, где заполнится record()*/
    QString getColumnNameById(const int column, const bool withTableName = false) const;
    QSqlField getColumnById(const int column) const;
    QSqlField getColumnByName(const QString &columnName) const;

    bool m_isFetchOnRefresh;

    bool updateValue(const int column, const qlonglong id, const QVariant &value) const;
    bool updateValue(const QString &columnName, const qlonglong id, const QVariant &value) const;

signals:
    void error(const QString &error) const;
    void startRefresh();
    void refreshed();
};

#endif // ABSTRACT_TABLE

