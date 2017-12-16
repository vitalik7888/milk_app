#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H

#include "HtmlElements.h"


class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlBuilder : public BaseHtmlElement {
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

#endif // HTMLBUILDER_H
