#ifndef TREEITEM_H
#define TREEITEM_H

#include "qtep.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QIcon>
#include <QSize>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Qtep {
namespace Gui {

class TreeItem
{
public:
  QTEP_LIB_DECL TreeItem();
  QTEP_LIB_DECL virtual ~TreeItem();

public:
  QTEP_LIB_DECL Qt::AlignmentFlag alignment() const;
  QTEP_LIB_DECL QColor backgroundColor() const;
  QTEP_LIB_DECL QBrush backgroundRole() const;
  QTEP_LIB_DECL QFont font() const;
  QTEP_LIB_DECL QColor foregroundColor() const;
  QTEP_LIB_DECL QBrush foregroundRole() const;
  QTEP_LIB_DECL QIcon icon() const;
  QTEP_LIB_DECL QSize sizeHint() const;
  QTEP_LIB_DECL QString statusText() const;
  QTEP_LIB_DECL QString text() const;
  QTEP_LIB_DECL QString toolTip() const;
  QTEP_LIB_DECL QString whatsThis() const;
  QTEP_LIB_DECL void setAlignment(Qt::AlignmentFlag alignment);
  QTEP_LIB_DECL void setBackgroundColor(const QColor & color);
  QTEP_LIB_DECL void setBackgroundRole(const QBrush & brush);
  QTEP_LIB_DECL void setFont(const QFont & font);
  QTEP_LIB_DECL void setForegroundColor(const QColor & color);
  QTEP_LIB_DECL void setForegroundRole(const QBrush & brush);
  QTEP_LIB_DECL void setIcon(const QIcon & icon);
  QTEP_LIB_DECL void setSizeHint(const QSize & size);
  QTEP_LIB_DECL void setStatusText(const QString & text);
  QTEP_LIB_DECL void setText(const QString & text);
  QTEP_LIB_DECL void setToolTip(const QString & text);
  QTEP_LIB_DECL void setWhatsThis(const QString & text);

public:
  QTEP_LIB_DECL void appendItem(TreeItem * childItem);
  QTEP_LIB_DECL bool loadFromXml(QXmlStreamReader & streamReader);
  QTEP_LIB_DECL void removeRow(int row);
  QTEP_LIB_DECL bool saveToXml(QXmlStreamWriter & streamWriter) const;

protected:
  virtual bool loadAttributes(QXmlStreamReader & streamReader);
  virtual bool saveAttributes(QXmlStreamWriter & streamWriter) const;

private:
  Qt::AlignmentFlag mAlignment;
  QColor mBackgroundColor;
  QBrush mBackgroundRole;
  QFont mFont;
  QColor mForegroundColor;
  QBrush mForegroundRole;
  QIcon mIcon;
  QSize mSizeHint;
  QString mStatusText;
  QString mText;
  QString mToolTip;
  QString mWhatsThis;
};

}
}

#endif // TREEITEM_H
