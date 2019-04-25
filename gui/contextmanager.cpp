#include "contextmanager.h"

#include <QDebug>

namespace Qtep {
namespace Gui {

ContextManager::ContextManager()
  : mCurrentContextId(0)
{
}

QStringList ContextManager::activeContextNames() const
{
  QStringList nameList;
  for (int i = 0; i < mActiveContexts.size(); i++) {
    QString name = contextName(mActiveContexts.at(i));
    nameList.append(name);
  }
  return nameList;
}

QList<int> ContextManager::activeContexts() const
{
  return mActiveContexts;
}

QList<int> ContextManager::allContexts() const
{
  return mAllContexts;
}

void ContextManager::appendContext(int contextId)
{
  if (mAllContexts.contains(contextId)) {
    qDebug() << "Context already exists";
    return;
  }

  if (mActiveContexts.contains(contextId)) {
    qDebug() << "Context already active";
    return;
  }

  emit aboutToAppendContext(contextId);
  mActiveContexts.append(contextId);
  emit finishedAppendContext(contextId);
}

void ContextManager::appendContext(const QString & contextName)
{
  appendContext(contextId(contextName));
}

int ContextManager::contextId(const QString & contextName) const
{
  if (!mNameToId.contains(contextName)) {
    return -1;
  }

  return mNameToId.value(contextName);
}

QStringList ContextManager::contextNames() const
{
  return mNameToId.keys();
}

QString ContextManager::contextName(int contextId) const
{
  for (int i = 0; i < mAllContexts.size(); i++) {
    int id = mAllContexts.at(i);
    if (id == contextId) {
      QString name = contextName(id);
      return name;
    }
  }
  return QString();
}

bool ContextManager::hasContext(const QList<int> & contextIds) const
{
  for (int i = 0; i < contextIds.size(); i++) {
    if (hasContext(contextIds.at(i))) {
      return true;
    }
  }
  return false;
}

bool ContextManager::hasContext(int context) const
{
  return mAllContexts.contains(context);
}

bool ContextManager::hasContext(const QString & contextName) const
{
  return mNameToId.contains(contextName);
}

int ContextManager::registerContext(const QString & contextName)
{
  if (hasContext(contextName)) {
    return contextId(contextName);
  }

  mCurrentContextId++;
  mAllContexts.append(mCurrentContextId);
  mNameToId[contextName] = mCurrentContextId;
  return mCurrentContextId;
}

void ContextManager::removeContext(const QString & contextName)
{
  removeContext(contextId(contextName));
}

void ContextManager::removeContext(int contextId)
{
  for (int i = 0; i < mActiveContexts.size(); i++) {
    int id = mActiveContexts.at(i);
    if (id == contextId) {
      emit aboutToRemoveContext(contextId);
      mActiveContexts.removeAt(i);
      emit finishedRemoveContext(contextId);
      emit contextChanged(mActiveContexts);
    }
  }
}

void ContextManager::setNewContext(int contextId)
{
  if (mActiveContexts.contains(contextId)) {
    qDebug() << "Context already active";
    return;
  }

  emit aboutToSetNewContext(contextId);

  mActiveContexts.clear();
  if (!mAllContexts.contains(contextId)) {
    qDebug() << "Attempting to activate unregistered context";
  }
  else {
    mActiveContexts.append(contextId);
  }

  emit finishedSetNewContext(contextId);
  emit contextChanged(mActiveContexts);
}

void ContextManager::setNewContext(const QString & contextName)
{
  setNewContext(contextId(contextName));
}

bool ContextManager::unregisterContext(int contextId)
{
  if (!hasContext(contextId)) {
    qDebug() << "Attempting to unregister a context that has not been registered";
    return false;
  }

  emit aboutToUnregisterContext(contextId);

  if (mActiveContexts.contains(contextId)) {
    removeContext(contextId);
  }

  QString name = contextName(contextId);
  mNameToId.remove(name);

  int index = mAllContexts.indexOf(contextId);
  mAllContexts.removeAt(index);

  emit finishedUnregisterContext(contextId);
  return true;
}

bool ContextManager::unregisterContext(const QString & contextName)
{
  return unregisterContext(contextId(contextName));
}

}
}
