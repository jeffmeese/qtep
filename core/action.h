#ifndef ACTION_H
#define ACTION_H

#include "qtep.h"

#include <QAction>
#include <QList>
#include <QString>

namespace Qtep {
namespace Core {

class Action
    : public QAction
{
  Q_OBJECT

public:
  QTEP_LIB_DECL Action(const QString & id, QAction * qtAction = nullptr);
  QTEP_LIB_DECL Action(const QString & id, const QString & text, QAction * qtAction = nullptr);

public:
  QTEP_LIB_DECL QList<int> currentContext() const;
  QTEP_LIB_DECL QString id() const;
  QTEP_LIB_DECL QAction * qtAction() const;
  QTEP_LIB_DECL bool supportsMultipleSelection() const;
  QTEP_LIB_DECL void setCurrentContext(const QList<int> & contexts);
  QTEP_LIB_DECL void setQtAction(QAction * qtAction);
  QTEP_LIB_DECL void setSupportsMultipleSelection(bool value);

protected slots:
  void handleChanged();

private:
  virtual void doSetContext(const QList<int> & contexts);

private:
  QString mId;
  QString mText;
  QAction * mQtAction;
  bool mSupportsMultipleSelection;
};

class Separator
    : public Action
{
public:
  QTEP_LIB_DECL Separator();
};

}
}

#endif // ACTION_H
