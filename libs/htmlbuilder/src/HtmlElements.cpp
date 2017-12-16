#include "HtmlElements.h"

#include "HtmlUtils.h"


HtmlContent::HtmlContent(const QString &content):
    BaseHtmlElement(),
    m_content(content)
{
}

// body
QString HtmlBody::toString() const
{
    return HtmlUtils::toTag(tagName(), this);
}
