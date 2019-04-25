#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include "qtep.h"

#include <QObject>
#include <QStandardItem>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Qtep {
namespace Core {

class Project;

class ProjectItem
    : public QObject
{
  Q_OBJECT

public:
  QTEP_LIB_DECL QString id() const;
  QTEP_LIB_DECL QString name() const;
  QTEP_LIB_DECL QString typeId() const;
  QTEP_LIB_DECL ProjectItem * parent() const;
  QTEP_LIB_DECL Project * project() const;
  QTEP_LIB_DECL void setName(const QString & name);
  QTEP_LIB_DECL void setProject(Project * project);

public:
  QTEP_LIB_DECL void addItem(ProjectItem * projectItem);
  QTEP_LIB_DECL ProjectItem * findItem(const QString & itemId);
  QTEP_LIB_DECL const ProjectItem * findItem(const QString & itemId) const;
  QTEP_LIB_DECL QList<ProjectItem*> findItems(const QString & name) const;
  QTEP_LIB_DECL ProjectItem * itemAt(int index);
  QTEP_LIB_DECL const ProjectItem * itemAt(int index) const;
  QTEP_LIB_DECL bool loadXml(QXmlStreamReader & reader);
  QTEP_LIB_DECL bool removeItem(const QString & itemId);
  QTEP_LIB_DECL bool saveXml(QXmlStreamWriter & writer) const;
  QTEP_LIB_DECL int totalItems() const;

protected:
  ProjectItem(const QString & typeId);
  ProjectItem(const QString & typeId, const QString & name);

protected:
  bool loadChildren(QXmlStreamReader & reader);
  bool saveChildren(QXmlStreamWriter & writer) const;

protected:
  virtual bool loadAttributes(QXmlStreamReader & reader) = 0;
  virtual bool saveAttributes(QXmlStreamWriter & writer) const = 0;

  // Due to some strange Qt rules about namespaces
  // the full namespace specification must be in the signal definition
signals:
  QTEP_LIB_DECL void itemAboutToBeRemoved(Qtep::Core::ProjectItem * item);
  QTEP_LIB_DECL void itemAdded(Qtep::Core::ProjectItem * item);
  QTEP_LIB_DECL void itemChanged();
  QTEP_LIB_DECL void itemRemoved();

private:
  QString mId;
  QString mName;
  QString mTypeId;
  ProjectItem * mParent;
  Project * mProject;
  QVector<ProjectItem*> mItems;
};

}
}

#endif // PROJECTITEM_H
