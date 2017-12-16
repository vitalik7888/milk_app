#ifndef HTMLTABLE_H
#define HTMLTABLE_H

#include "HtmlElement.h"

// header cell
class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTableHeader : public HtmlElement {
public:
    HtmlTableHeader(const HtmlElements &children = {}): HtmlElement(children) {  }
    QString tagName() const Q_DECL_OVERRIDE { return "th"; }
};

// header row
using TableHeaders = QList<HtmlTableHeader *>;

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTableHeaderRow : public BaseHtmlElement {
public:
    HtmlTableHeaderRow(const TableHeaders &headers = {}, const HtmlAttributes &attributes = {});
    ~HtmlTableHeaderRow();

    QString tagName() const Q_DECL_OVERRIDE { return "tr"; }
    QString toString() const Q_DECL_OVERRIDE;

    HtmlTableHeaderRow *addHeader(HtmlTableHeader *header);
    HtmlTableHeaderRow *setHeaders(const TableHeaders &headers);

private:
    TableHeaders m_headers;
};

// cell
class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTableCell : public HtmlElement {
public:
    HtmlTableCell(const HtmlElements &children = {}) : HtmlElement(children) {}
    virtual QString tagName() const Q_DECL_OVERRIDE { return "td"; }
};

// row
using TableCells = QList<HtmlTableCell *>;

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTableRow : public BaseHtmlElement {
public:
    HtmlTableRow(const TableCells &cells = {}, const HtmlAttributes &attributes = {});
    ~HtmlTableRow();

    QString tagName() const Q_DECL_OVERRIDE { return "tr"; }
    QString toString() const Q_DECL_OVERRIDE;

    HtmlTableRow *addCell(HtmlTableCell *cell);
    HtmlTableRow *setCells(const TableCells &cells);

private:
    TableCells m_cells;
};

// caption
class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTableCaption : public HtmlElement {
public:
    HtmlTableCaption(const HtmlElements &children = {}) : HtmlElement(children) {}
    QString tagName() const Q_DECL_OVERRIDE { return "caption"; }
};

// table
using TableRows = QList<HtmlTableRow *>;

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlTable : public HtmlElement {
public:
    HtmlTable(HtmlTableCaption *caption = Q_NULLPTR, const HtmlAttributes &attributes = {});
    ~HtmlTable();

    QString tagName() const Q_DECL_OVERRIDE { return "table"; }
    QString toString() const Q_DECL_OVERRIDE;

    HtmlTable *setCaption(HtmlTableCaption *caption);

    HtmlTable *setHeaderRow(HtmlTableHeaderRow *headerRow);

    HtmlTable *addRow(HtmlTableRow *row);
    HtmlTable *setRows(const TableRows &rows);

private:
    HtmlTableCaption *m_caption;
    HtmlTableHeaderRow *m_headerRow;
    TableRows m_rows;
};

#endif // HTMLTABLE_H
