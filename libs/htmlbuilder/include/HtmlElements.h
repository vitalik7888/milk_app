#ifndef HTMLELEMENTS_H
#define HTMLELEMENTS_H

#include "HtmlElement.h"

class QFont;
class QColor;

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlContent : public BaseHtmlElement {
public:
    HtmlContent(const QString &content);

    virtual QString tagName() const Q_DECL_OVERRIDE { return ""; }
    virtual QString toString() const Q_DECL_OVERRIDE { return m_content; }

private:
    QString m_content;
};

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlBody : public HtmlElement {
public:
    HtmlBody(const HtmlAttributes &attributes = {}, const HtmlElements &children = {}):
        HtmlElement(attributes, children) {}
    QString tagName() const Q_DECL_OVERRIDE { return "body"; }
    QString toString() const Q_DECL_OVERRIDE;
};

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlComment : public BaseHtmlElement {
public:
    HtmlComment(const QString &comment): BaseHtmlElement(), m_comment(comment) {}
    QString toString() const Q_DECL_OVERRIDE { return QString("<!-- %1 -->").arg(m_comment); }

private:
    QString m_comment;
};

class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlFont : public HtmlElement {
public:
    HtmlFont(const QFont &font, const QColor &color, const HtmlElements &children = {});

    QString tagName() const Q_DECL_OVERRIDE { return "font"; }
};

#endif // HTMLELEMENTS_H
