#ifndef HTMLUTILS_H
#define HTMLUTILS_H

#include "htmlbuilderlibrary_global.h"
// Qt
#include <QString>

class BaseHtmlElement;
class HtmlElement;


class HTMLBUILDERLIBRARYSHARED_EXPORT HtmlUtils
{
public:
    static QString getElementsString(const HtmlElement *element);
    static QString getAttributesString(const BaseHtmlElement *element);

    static QString toOpenedTag(const QString &tagName, const BaseHtmlElement *element = Q_NULLPTR);
    static QString toClosedTag(const QString &tagName);
    static QString toBaseTag(const QString &tagName, const BaseHtmlElement *element);
    static QString toTag(const QString &tagName, const HtmlElement *element);
};

#endif // HTMLUTILS_H
