#ifndef VIEWUTILS_H
#define VIEWUTILS_H

#include "dbconstants.h"
// Qt
#include <QVariant>

DB_BEGIN_NAMESPACE
    class Table;
DB_END_NAMESPACE
class QToolButton;
class QWidget;
class QAbstractItemView;
class QComboBox;


class ViewUtils
{
public:
  static bool yesNoWarnMsgBox(QWidget *parent, const QString &question);
  static bool showWarnMsgIfNoRows(QWidget *parent, const QString &title, DB_NAMESPACE::Table *table);
  static bool isNeesAddItem(QWidget *parent, DB_NAMESPACE::Table *table);

  static milk_id getIdFromDialog(DB_NAMESPACE::Table *table, const QString &title = QString(),
                                   QWidget *parent = nullptr);
  static QModelIndex getIndexFromModelById(DB_NAMESPACE::Table *table, const int column, const milk_id id);
  static QVariant getCurValueFromComboBoxModel(const QComboBox *combobox, const int column);
  static QVariant getCurValueFromItemViewModel(const QAbstractItemView *itemView, const int column);

  static void showMsgIfDbNotChoosed(QWidget *parent);
};

#endif // VIEWUTILS_H
