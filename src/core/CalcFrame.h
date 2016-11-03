#ifndef CALCFRAME_H
#define CALCFRAME_H

// Qt
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
class QTableWidgetItem;


class TableWidgetItemBuilder {
public:
    TableWidgetItemBuilder();

    TableWidgetItemBuilder *setNum(const double value, const char f = 'f', const int prec = 2);
    TableWidgetItemBuilder *setFont(const QFont &font);
    TableWidgetItemBuilder *setBackColor(const QColor &backColor);
    TableWidgetItemBuilder *setText(const QString &text);

    TableWidgetItemBuilder *reset();
    QTableWidgetItem *get();

private:
    QString m_text;
    QColor  m_backColor;
    QFont   m_font;
};

class CalcFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CalcFrame(QWidget *parent = 0);
    ~CalcFrame();

    void setup();
    void setMainWindow(MainWindow *mainWindow);

    bool isCalcByDeliverer() const;
    bool isCalcByDate() const;
    bool isCalcByMilkPoint() const;

public slots:
    void chooseDate();
    void calc();
    void printCalc();

private:
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

    Ui::CalcFrame *ui;
    MainWindow *m_mainWindow;

    QString getWhereQuery();
    void refreshTableWidgetCalc();

    static int toInt(const Columns column);
};

#endif // CALCFRAME_H
