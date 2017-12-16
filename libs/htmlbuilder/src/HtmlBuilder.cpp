#include "HtmlBuilder.h"

// Qt
#include <QtGui/QColor>
#include <QtGui/QFont>


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
