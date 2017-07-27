#include "PrintTableWidget.h"

// Qt
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QTextTable>
#include <QDebug>

#define HEADER_ROW_POS 0

PrintTable::PrintTable(const int columnsCount, const QTextTableFormat &tableFormat, QWidget *parent) :
    QWidget(parent),
    m_isShowPreview(true),
    m_textDoc(new QTextDocument),
    m_table(nullptr),
    m_cursor(m_textDoc)
{
    setObjectName("PrintTable");

    m_textDoc->setParent(this);

    m_cursor.movePosition(QTextCursor::Start);

    m_tableFrameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    m_cursor.insertFrame(m_tableFrameFormat);

    m_table = m_cursor.insertTable(1, columnsCount, tableFormat);
}

PrintTable::~PrintTable()
{
}

QTextDocument *PrintTable::textDoc() const
{
    return m_textDoc;
}

QTextCursor &PrintTable::cursor()
{
    return m_cursor;
}

void PrintTable::setHeaders(const QStringList &headersNames)
{
    for(int i = 0; i < headersNames.size(); ++i)
    {
        m_cursor = m_table->cellAt(HEADER_ROW_POS, i).firstCursorPosition();
        m_cursor.insertText(headersNames[i], m_tableHeadersFormat);
    }
}

void PrintTable::addRow(const QStringList &row, const int mergeColCount, const int mergeFrom)
{
    const auto colCount = row.size();

    int rowPos = m_table->rows();
    m_table->insertRows(rowPos, 1);

    for (int i = 0; i < colCount; ++i) {
        m_cursor = m_table->cellAt(rowPos, i).firstCursorPosition();
        m_cursor.insertText(row[i], m_tableBodyTextFormat);
    }

    if (mergeColCount > 0)
        m_table->mergeCells(rowPos, mergeFrom, 1, mergeColCount);
}

void PrintTable::addRow(const QStringList &row, const QTextCharFormat &textFormat, const int mergeColCount, const int mergeFrom)
{
    const auto colCount = row.size();

    int rowPos = m_table->rows();
    m_table->insertRows(rowPos, 1);

    for (int i = 0; i < colCount; ++i) {
        m_cursor = m_table->cellAt(rowPos, i).firstCursorPosition();
        m_cursor.insertText(row[i], textFormat);
    }

    if (mergeColCount > 0)
        m_table->mergeCells(rowPos, mergeFrom, 1, mergeColCount);
}

QTextCharFormat &PrintTable::getTableBodyTextFormat()
{
    return m_tableBodyTextFormat;
}

QTextCharFormat &PrintTable::getTableHeadersFormat()
{
    return m_tableHeadersFormat;
}

QTextFrameFormat &PrintTable::getTableFrameFormat()
{
    return m_tableFrameFormat;
}

QTextTable *PrintTable::getTable() const
{
    return m_table;
}

void PrintTable::showDialog()
{
    QPrinter printer(QPrinter::HighResolution);

    if(!m_isShowPreview)
    {
        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Печать документа"));
        connect(&dialog, SIGNAL(accepted(QPrinter*)), this, SLOT(print(QPrinter*)));
        dialog.exec();
    } else {
        QPrintPreviewDialog printPreview(&printer, this);
        printPreview.setWindowFlags(Qt::Window);
        connect(&printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        printPreview.exec();
    }
}

void PrintTable::print(QPrinter *printer)
{
    m_textDoc->print(printer);
}
