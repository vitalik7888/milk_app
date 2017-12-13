#ifndef HTMLELEMENTS_H
#define HTMLELEMENTS_H

#include "HtmlElement.h"

class QFont;
class QColor;

class HtmlContent : public BaseHtmlElement {
public:
    HtmlContent(const QString &content);

    virtual QString tagName() const Q_DECL_OVERRIDE { return ""; }
    virtual QString toString() const Q_DECL_OVERRIDE { return m_content; }

private:
    QString m_content;
};

class HtmlBody : public HtmlElement {
public:
    HtmlBody(const HtmlAttributes &attributes = {}, const HtmlElements &children = {}):
        HtmlElement(attributes, children) {}
    QString tagName() const Q_DECL_OVERRIDE { return "body"; }
    QString toString() const Q_DECL_OVERRIDE;
};

class HtmlBuilder : public BaseHtmlElement {
public:
    HtmlBuilder() : BaseHtmlElement() {  }

    QString tagName() const Q_DECL_OVERRIDE { return "html"; }
    QString toString() const Q_DECL_OVERRIDE {
        return QString("<!DOCTYPE html>"
                       "<html>"
                       "<head>"
                       "<style>%1</style>"
                       "<title>%2</title>"
                       "</head>"
                       "%3"
                       "</html>")
                .arg(m_style)
                .arg(m_title)
                .arg(m_body.toString());
    }

    HtmlBuilder *addBodyElement(HtmlElement *element) {
        m_body.addElement(element);
        return this;
    }

    QString style() const { return m_style; }
    HtmlBuilder *setStyle(const QString &style);

    QString title() const { return m_title; }
    HtmlBuilder *setTitle(const QString &title);

private:
    QString m_style;
    QString m_title;
    HtmlBody m_body;
};

class HtmlComment : public BaseHtmlElement {
public:
    HtmlComment(const QString &comment): BaseHtmlElement(), m_comment(comment) {}
    QString toString() const Q_DECL_OVERRIDE { return QString("<!-- %1 -->").arg(m_comment); }

private:
    QString m_comment;
};

class HtmlFont : public HtmlElement {
public:
    HtmlFont(const QFont &font, const QColor &color, const HtmlElements &children = {});

    QString tagName() const Q_DECL_OVERRIDE { return "font"; }
};

#endif // HTMLELEMENTS_H
