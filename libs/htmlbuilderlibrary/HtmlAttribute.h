#ifndef HTMLATTRIBUTE_H
#define HTMLATTRIBUTE_H

#include "htmlbuilderlibrary_global.h"
// Qt
#include <QString>


class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlAttribute
{
public:
    HtmlAttribute(const QString &attr);

    QString toString() const;

protected:
    QString m_attribute;
};

#endif // HTMLATTRIBUTE_H
