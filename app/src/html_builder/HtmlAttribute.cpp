#include "HtmlAttribute.h"

HtmlAttribute::HtmlAttribute(const QString &attr):
    m_attribute(attr)
{

}

QString HtmlAttribute::toString() const
{
    return m_attribute;
}




