#include "HtmlTable.h"

#include "HtmlUtils.h"


// header row
HtmlTableHeaderRow::HtmlTableHeaderRow(const TableHeaders &headers,
                                       const HtmlAttributes &attributes):
    BaseHtmlElement(attributes),
    m_headers(headers)
{
}

HtmlTableHeaderRow::~HtmlTableHeaderRow()
{
    qDeleteAll(m_headers);
}

QString HtmlTableHeaderRow::toString() const
{
    QString result;
    result.append(HtmlUtils::toOpenedTag(tagName(), this));
    for (const auto &header : m_headers)
        result.append(header->toString());
    result.append(HtmlUtils::toClosedTag(tagName()));

    return result;
}

HtmlTableHeaderRow *HtmlTableHeaderRow::addHeader(HtmlTableHeader *header)
{
    m_headers.append(header);
    return this;
}

HtmlTableHeaderRow *HtmlTableHeaderRow::setHeaders(const TableHeaders &headers)
{
    m_headers = headers;
    return this;
}

// row
HtmlTableRow::HtmlTableRow(const TableCells &cells, const HtmlAttributes &attributes):
    BaseHtmlElement(attributes),
    m_cells(cells)
{

}

HtmlTableRow::~HtmlTableRow()
{
    qDeleteAll(m_cells);
}

QString HtmlTableRow::toString() const
{
    QString result;
    result.append(HtmlUtils::toOpenedTag(tagName(), this));
    for (const auto &cell : m_cells)
        result.append(cell->toString());
    result.append(HtmlUtils::toClosedTag(tagName()));

    return result;
}

HtmlTableRow *HtmlTableRow::addCell(HtmlTableCell *cell)
{
    m_cells.append(cell);
    return this;
}

HtmlTableRow *HtmlTableRow::setCells(const TableCells &cells)
{
    m_cells = cells;
    return this;
}

// table
HtmlTable::HtmlTable(HtmlTableCaption *caption, const HtmlAttributes &attributes) :
    HtmlElement(attributes),
    m_caption(caption),
    m_headerRow(Q_NULLPTR)
{

}

HtmlTable::~HtmlTable()
{
    if (m_headerRow)
        delete m_headerRow;
}

QString HtmlTable::toString() const
{
    QString result;
    result.append(HtmlUtils::toOpenedTag(tagName(), this));
    result.append(m_caption->toString());
    result.append(m_headerRow->toString());
    for (const auto &row : m_rows)
        result.append(row->toString());
    result.append(HtmlUtils::toClosedTag(tagName()));

    return result;
}

HtmlTable *HtmlTable::setHeaderRow(HtmlTableHeaderRow *headerRow)
{
    m_headerRow = headerRow;
    return this;
}

HtmlTable *HtmlTable::addRow(HtmlTableRow *row)
{
    m_rows.append(row);
    return this;
}

HtmlTable *HtmlTable::setRows(const TableRows &rows)
{
    m_rows = rows;
    return this;
}

HtmlTable *HtmlTable::setCaption(HtmlTableCaption *caption)
{
    m_caption = caption;
    return this;
}
