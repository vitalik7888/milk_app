#ifndef HTMLATTRIBUTE_H
#define HTMLATTRIBUTE_H

#include <QString>


class HtmlAttribute
{
public:
    HtmlAttribute(const QString &attr);

    QString toString() const;

protected:
    QString m_attribute;
};

#endif // HTMLATTRIBUTE_H
