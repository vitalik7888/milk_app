#ifndef CALCFRAME_H
#define CALCFRAME_H

#include <QFrame>
#include <QVector>
#include <QDate>

#include <QTextTableFormat>

namespace Ui {
class CalcFrame;
}
class MainWindow;
class QSqlQuery;
class QTextDocument;
class QTextTable;


class CalcFrame : public QFrame
{
    Q_OBJECT

    class Item {
    public:
        Item();
        Item(const QString &_delivererName, const QString &_milkPointName = QString(), const QDate &_deliveryDate = QDate(),
             const double _priceLiter = .0, const double _liters = .0, const double _fat = .0,
             const double _protein = .0, const double _fatUnits = .0, const double _rankWeight = .0, const double _paymentWithOutPremium = .0,
             const double _premiumForFat = .0, const double _sum = .0);

        QString delivererName;
        QString milkPointName;
        QDate deliveryDate;
        double priceLiter;
        double liters;
        double fat;
        double protein;
        double fatUnits;
        double rankWeight;
        double paymentWithOutPremium;
        double premiumForFat;
        double sum;
    };

    typedef QMultiHash<qlonglong, Item> CalcItems;

public:
    enum class Columns: int {
        Name = 0,
        MilkPointName,
        Date,
        PriceLiter,
        Liters,
        Fat,
        Protein,
        FatUnits,
        RankWeight,
        PayWithOutPrem,
        Premium,
        Sum
    };

    explicit CalcFrame(QWidget *parent = 0);
    ~CalcFrame();

    void calc();
    void setup();
    void setMainWindow(MainWindow *mainWindow);

    bool isCalcByDeliverer() const;
    bool isCalcByDate() const;
    bool isCalcByMilkPoint() const;

public slots:
    void chooseDate();
    void printCalc();

private:
    Ui::CalcFrame *ui;
    MainWindow *m_mainWindow;

    QString getPrepQueryStr() const;
    bool addBindValueToQuery(QSqlQuery &query);
    CalcItems getItemsData();
    void fillTableWidget(const CalcItems &items);
    void setTableWidgetItem(const int row, const Item &item, const QColor &color, const QFont &font);

    QString getValueFromItem(const Item &item, const Columns column) const;
    void setAllCalc(Item &item);
    void setSomeCalc(Item &item);
    void sumItems(Item &left, const Item &right);
};

#endif // CALCFRAME_H
