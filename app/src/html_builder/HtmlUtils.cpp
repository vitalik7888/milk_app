#include "HtmlUtils.h"

#include "HtmlElement.h"


QString HtmlUtils::getElementsString(const HtmlElement *element)
{
    QString result;
    for (auto _element : element->elements())
        result.append(_element->toString());

    return result;
}

QString HtmlUtils::getAttributesString(const BaseHtmlElement *element)
{
    QString result;
    for (const auto &attribute : element->attributes())
        result.append(attribute.toString() + " ");

    return result.simplified();
}

QString HtmlUtils::toBaseTag(const QString &tagName, const BaseHtmlElement *element) {
    return toOpenedTag(tagName, element) + toClosedTag(tagName);
}

QString HtmlUtils::toOpenedTag(const QString &tagName, const BaseHtmlElement *element)
{
    const QString attributes = element == Q_NULLPTR ? "" : getAttributesString(element);
    return "<" + tagName + " " + attributes + ">";
}

QString HtmlUtils::toClosedTag(const QString &tagName)
{
    return "</" + tagName + ">";
}

QString HtmlUtils::toTag(const QString &tagName, const HtmlElement *element) {
    return toOpenedTag(tagName, element) + getElementsString(element) + toClosedTag(tagName);
}
