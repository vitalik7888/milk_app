#include "BaseHtmlElement.h"
#include "HtmlUtils.h"


BaseHtmlElement::BaseHtmlElement(const HtmlAttributes &attributes):
    m_attributes(attributes)
{

}

BaseHtmlElement::~BaseHtmlElement()
{

}

QString BaseHtmlElement::toString() const
{
    return HtmlUtils::toBaseTag(tagName(), this);
}

BaseHtmlElement *BaseHtmlElement::addAttribute(const HtmlAttribute &attribute)
{
    m_attributes.append(attribute);
    return this;
}

BaseHtmlElement *BaseHtmlElement::setAttributes(const HtmlAttributes &attributes)
{
    m_attributes = attributes;
    return this;
}


