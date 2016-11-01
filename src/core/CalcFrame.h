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
             const float _priceLiter = .0f, const float _liters = .0f, const float _fat = .0f,
             const float _protein = .0f, const float _fatUnits = .0f, const float _rankWeight = .0f, const float _paymentWithOutPremium = .0f,
             const float _premiumForFat = .0f, const float _sum = .0f);

        QString delivererName;
        QString milkPointName;
        QDate deliveryDate;
        float priceLiter;
        float liters;
        float fat;
        float protein;
        float fatUnits;
        float rankWeight;
        float paymentWithOutPremium;
        float premiumForFat;
        float sum;
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
