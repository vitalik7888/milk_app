#include "HtmlElement.h"

#include "HtmlUtils.h"


HtmlElement::HtmlElement(const HtmlAttributes &attributes, const HtmlElements &children):
    BaseHtmlElement(attributes),
    m_elements(children)
{

}

HtmlElement::HtmlElement(const HtmlElements &children):
    HtmlElement({}, children)
{

}

HtmlElement::~HtmlElement()
{
    qDeleteAll(m_elements);
    m_elements.clear();
}

HtmlElement *HtmlElement::addElement(BaseHtmlElement *element)
{
    m_elements.push_back(element);

    return this;
}

QString HtmlElement::toString() const
{
    return HtmlUtils::toTag(tagName(), this);
}
