#ifndef PROJECT_H
#define PROJECT_H

#include "qtep.h"

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Qtep {
namespace Core {

class ProjectItem;

class Project
    : public QObject
{
  Q_OBJECT

public:
  QTEP_LIB_DECL Project();

public:
  QTEP_LIB_DECL QString fileName() const;
  QTEP_LIB_DECL bool modified() const;
  QTEP_LIB_DECL QString name() const;
  QTEP_LIB_DECL void setModified(bool modified = true);
  QTEP_LIB_DECL void setName(const QString & name);

public:
  QTEP_LIB_DECL void addItem(ProjectItem * projectItem);
  QTEP_LIB_DECL ProjectItem * findItem(const QString & itemId);
  QTEP_LIB_DECL const ProjectItem * findItem(const QString & itemId) const;
  QTEP_LIB_DECL QList<ProjectItem*> findItems(const QString & name) const;
  QTEP_LIB_DECL ProjectItem * itemAt(int index);
  QTEP_LIB_DECL const ProjectItem * itemAt(int index) const;
  QTEP_LIB_DECL bool load(const QString & fileName);
  QTEP_LIB_DECL bool loadXml(QXmlStreamReader & reader);
  QTEP_LIB_DECL void newProject();
  QTEP_LIB_DECL bool removeItem(const QString & itemId);
  QTEP_LIB_DECL bool save(const QString & fileName);
  QTEP_LIB_DECL bool saveXml(QXmlStreamWriter & writer) const;
  QTEP_LIB_DECL int totalItems() const;

  // Due to some strange Qt rules about namespaces
  // the full namespace specification must be in the signal definition
signals:
  QTEP_LIB_DECL void itemAboutToBeRemoved(Qtep::Core::ProjectItem * item);
  QTEP_LIB_DECL void itemAdded(Qtep::Core::ProjectItem * item);
  QTEP_LIB_DECL void itemRemoved();
  QTEP_LIB_DECL void modified(bool modified);
  QTEP_LIB_DECL void nameChanged(const QString & newName);

private:
  bool mModified;
  QString mFileName;
  QString mName;
  QVector<ProjectItem*> mItems;
};

}
}

#endif // PROJECT_H
