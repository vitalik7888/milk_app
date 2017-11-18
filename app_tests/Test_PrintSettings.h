#ifndef TEST_PRINTSETTINGS_H
#define TEST_PRINTSETTINGS_H

#include <QObject>

class PrintSettings;
class QSignalSpy;


class Test_PrintSettings : public QObject
{
    Q_OBJECT
public:
    explicit Test_PrintSettings(QObject *parent = nullptr);

private slots:
    void testEmptyConstructor();
    void testMethods();
    void testReset();
    void testSignalTextFont();
    void testSignalCaptionTextFont();
    void testSignalCaptionColor();
    void testSignalTableWidth();
    void testSignalTableBorderWidth();
    void testSignalTableBorderStyle();
    void testSignalCellSpacing();
    void testSignalCellPadding();
    void testSignalTableBorderColor();
    void testSignalTableHeaderFont();
    void testSignalTableHeaderColor();
    void testSignalTableTextFont();
    void testSignalTableTextColor();
    void testSignalTableResultFont();
    void testSignalTableResultColor();

private:
    void compare(const PrintSettings &ps,
                 const QFont &textFont,
                 const QFont &captionTextFont,
                 const QColor &captionColor,
                 const int tableWidth,
                 const int tableBorderWidth,
                 const int tableBorderStyle,
                 const int cellSpacing,
                 const int cellPadding,
                 const QColor &tableBorderColor,
                 const QFont &tableHeaderFont,
                 const QColor &tableHeaderColor,
                 const QFont &tableTextFont,
                 const QColor &tableTextColor,
                 const QFont &tableResultFont,
                 const QColor &tableResultColor);

    void compareDefault(const PrintSettings &ps);

    void compareSignal(const QSignalSpy &spy, const QVariant &value, const int count);
};

#endif // TEST_PRINTSETTINGS_H
