#ifndef BASEHTMLELEMENT_H
#define BASEHTMLELEMENT_H

#include "HtmlAttribute.h"
// Qt
#include <QList>

using HtmlAttributes = QList<HtmlAttribute>;


class HTMLBUILDERLIBRARYSHARED_EXPORT BaseHtmlElement
{
public:
    BaseHtmlElement(const HtmlAttributes &attributes = {});
    virtual ~BaseHtmlElement();

    virtual QString tagName() const = 0;
    virtual QString toString() const;

    HtmlAttributes attributes() const { return m_attributes; }
    BaseHtmlElement *addAttribute(const HtmlAttribute &attribute);
    BaseHtmlElement *setAttributes(const HtmlAttributes &attributes);

protected:
    HtmlAttributes m_attributes;
};

#endif // BASEHTMLELEMENT_H
