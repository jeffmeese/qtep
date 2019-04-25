#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "qtep.h"

#include <QAction>
#include <QList>
#include <QMap>

namespace Qtep {

namespace Core {
class Action;
}

namespace Gui {

class ActionManager
    : public QObject
{
  Q_OBJECT

public:
  QTEP_LIB_DECL ActionManager();

public:
  QTEP_LIB_DECL Core::Action * action(const QString & id) const;
  QTEP_LIB_DECL Core::Action * registerAction(const QString & actionId, const QList<int> & contexts = QList<int>());
  QTEP_LIB_DECL Core::Action * registerAction(const QString & actionId, QAction * action, const QList<int> & contexts = QList<int>());
  QTEP_LIB_DECL bool unregisterAction(const QString & actionId);

public slots:
  QTEP_LIB_DECL void handleContextChanged(const QList<int> & contexts);

private:
  typedef QMap<QString, Core::Action*> ActionMap;

private:
  ActionMap mActionMap;
};

}
}

#endif // ACTIONMANAGER_H
