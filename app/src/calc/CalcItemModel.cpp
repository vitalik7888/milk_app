#include "CalcItemModel.h"


CalcItemModel::CalcItemModel(QObject *parent):
    QAbstractItemModel(parent),
    m_dateFormat("yy-MMMM-ddd"),
    m_prec(2)
{
    m_root = new CalculatedItem(this);
}

CalcItemModel::CalcItemModel(CalculatedItem *calcItem, QObject *parent):
    CalcItemModel(parent)
{
    calcItem->setParent(m_root);
    m_root->addItem(calcItem);
}

CalcItemModel::~CalcItemModel()
{
    delete m_root;
}

QModelIndex CalcItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CalculatedItem *parentItem = !parent.isValid() ?
                m_root :
                static_cast<CalculatedItem*>(parent.internalPointer());

    CalculatedItem *childItem = parentItem->item(row);
    return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex CalcItemModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    auto childItem = static_cast<CalculatedItem *>(child.internalPointer());
    auto parentItem = childItem->parent();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CalcItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    return !parent.isValid() ? m_root->itemsCount() :
                               static_cast<CalculatedItem *>(parent.internalPointer())->itemsCount();
}

int CalcItemModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ?
                static_cast<CalculatedItem *>(parent.internalPointer())->columnCount() :
                m_root->columnCount();
}

QVariant CalcItemModel::data(const QModelIndex &_index, int role) const
{
    if (!_index.isValid())
        return QVariant();

    if (role > Qt::UserRole) {
        auto item = static_cast<CalculatedItem *>(_index.internalPointer());
        QModelIndex modelIndex = this->index(_index.row(), role - Qt::UserRole - 1,
                                             parent(_index));

        const int column = modelIndex.column();
        const auto data = item->data(static_cast<CalculatedItem::Columns>(column));
        if (data.type() == QVariant::Date) {
            if (!data.isValid())
                return QVariant("");
            return QVariant(data.toDate().toString(m_dateFormat));
        } else if (data.type() == QVariant::Double) {
            if (column == static_cast<int>(CalculatedItem::Columns::Price) && data.toDouble() <= .0)
                return QVariant("");
            return QVariant(QString::number(data.toDouble(), 'f', m_prec));
        }
        return data;
    }

    return QVariant();
}

QVariant CalcItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_root->data(static_cast<CalculatedItem::Columns>(section));

    return QVariant();
}

Qt::ItemFlags CalcItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> CalcItemModel::roleNames() const
{
    return {
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Name), "name"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Date), "date"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::MilkPointName), "mpName"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Price), "price"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Liters), "liters"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Fat), "fat"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Protein), "protein"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::FatUnits), "fatUnits"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::RankWeight), "rankWeight"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::PaymentWithOutPremium), "payment"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::PremiumForFat), "premium"},
        {Qt::UserRole + 1 + static_cast<int>(CalculatedItem::Columns::Sum), "sum"}

    };
}

void CalcItemModel::setDateFormat(const QString &dateFormat)
{
    m_dateFormat = dateFormat;
}

void CalcItemModel::setPrec(int prec)
{
    m_prec = prec;
}
