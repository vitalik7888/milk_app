#include "HtmlElements.h"

#include "HtmlUtils.h"
// Qt
#include <QColor>
#include <QFont>


HtmlContent::HtmlContent(const QString &content):
    BaseHtmlElement(),
    m_content(content)
{
}

// body
QString HtmlBody::toString() const {
    return HtmlUtils::toTag(tagName(), this);
}

HtmlBuilder *HtmlBuilder::setStyle(const QString &style)
{
    m_style = style;
    return this;
}

HtmlBuilder *HtmlBuilder::setTitle(const QString &title)
{
    m_title = title;
    return this;
}

HtmlFont::HtmlFont(const QFont &font, const QColor &color, const HtmlElements &children):
    HtmlElement({
{QString("face=\"%1\"").arg(font.family())},
{QString("size=\"%1\"").arg(font.weight())},
{QString("color=\"%1\"").arg(color.name())},
                },
                children)
{

}
