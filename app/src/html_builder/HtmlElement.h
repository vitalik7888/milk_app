#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include "BaseHtmlElement.h"

class HtmlElement;

using HtmlElements = QList<BaseHtmlElement *>;


class HtmlElement : public BaseHtmlElement
{
public:
    HtmlElement(const HtmlAttributes &attributes = {}, const HtmlElements &children = {});
    HtmlElement(const HtmlElements &children = {});
    virtual ~HtmlElement();

    virtual QString toString() const Q_DECL_OVERRIDE;

    HtmlElements elements() const { return m_elements; }
    HtmlElement *addElement(BaseHtmlElement *element);

protected:
    HtmlElements m_elements;
};

#endif // HTMLELEMENT_H
