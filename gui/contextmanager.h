#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include "qtep.h"

#include <QList>
#include <QObject>
#include <QString>

namespace Qtep {
namespace Gui {

class ContextManager
    : public QObject
{
  Q_OBJECT

public:
  QTEP_LIB_DECL ContextManager();

public:
  QTEP_LIB_DECL QStringList activeContextNames() const;
  QTEP_LIB_DECL QList<int> activeContexts() const;
  QTEP_LIB_DECL QList<int> allContexts() const;
  QTEP_LIB_DECL void appendContext(int contextId);
  QTEP_LIB_DECL void appendContext(const QString & contextName);
  QTEP_LIB_DECL int contextId(const QString & contextName) const;
  QTEP_LIB_DECL QStringList contextNames() const;
  QTEP_LIB_DECL QString contextName(int contextId) const;
  QTEP_LIB_DECL bool hasContext(const QList<int> & contextIds) const;
  QTEP_LIB_DECL bool hasContext(int context) const;
  QTEP_LIB_DECL bool hasContext(const QString & contextName) const;
  QTEP_LIB_DECL int registerContext(const QString & context);
  QTEP_LIB_DECL void removeContext(const QString & id);
  QTEP_LIB_DECL void removeContext(int contextId);
  QTEP_LIB_DECL void setNewContext(int contextId);
  QTEP_LIB_DECL void setNewContext(const QString & contextName);
  QTEP_LIB_DECL bool unregisterContext(int contextId);
  QTEP_LIB_DECL bool unregisterContext(const QString & contextName);

signals:
  QTEP_LIB_DECL void aboutToAppendContext(int contextId);
  QTEP_LIB_DECL void aboutToRemoveContext(int contextId);
  QTEP_LIB_DECL void aboutToSetNewContext(int contextId);
  QTEP_LIB_DECL void aboutToUnregisterContext(int contextId);
  QTEP_LIB_DECL void contextChanged(const QList<int> & contexts);
  QTEP_LIB_DECL void finishedAppendContext(int contextId);
  QTEP_LIB_DECL void finishedRemoveContext(int contextId);
  QTEP_LIB_DECL void finishedSetNewContext(int contextId);
  QTEP_LIB_DECL void finishedUnregisterContext(int contextId);

private:
  QList<int> mAllContexts;
  QList<int> mActiveContexts;
  QHash<QString, int> mNameToId;
  int mCurrentContextId;
};

}
}

#endif // CONTEXTMANAGER_H
