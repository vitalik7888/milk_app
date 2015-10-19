#ifndef PRINT_TABLE_H
#define PRINT_TABLE_H

#include <QWidget>
#include <QTextCursor>

class QTextDocument;
class QPrinter;


class PrintTable : public QWidget
{
    Q_OBJECT
public:

    explicit PrintTable(const int columnsCount, const QTextTableFormat &tableFormat = QTextTableFormat(),
                        QWidget *parent = 0);
    ~PrintTable();

    QTextDocument *textDoc() const;
    QTextCursor &cursor();
    QTextTable *getTable() const;

    void setHeaders(const QStringList &headersNames);
    void addRow(const QStringList &row, const int mergeColCount = 0, const int mergeFrom = 0);
    void addRow(const QStringList &row, const QTextCharFormat &textFormat, const int mergeColCount = 0, const int mergeFrom = 0);

    QTextCharFormat &getTableBodyTextFormat();
    QTextCharFormat &getTableHeadersFormat();
    QTextFrameFormat &getTableFrameFormat();

private:
    bool m_isShowPreview;

    QTextDocument *m_textDoc;
    QTextTable *m_table;
    QTextCursor m_cursor;

    QTextCharFormat m_tableHeadersFormat;
    QTextCharFormat m_tableBodyTextFormat;
    QTextFrameFormat m_tableFrameFormat;


private slots:
    void print(QPrinter *printer);

public slots:
    void showDialog();
};

#endif // PRINT_TABLE_H
