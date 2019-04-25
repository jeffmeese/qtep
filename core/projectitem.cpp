#include "projectitem.h"
#include "project.h"

#include <QUuid>

namespace Qtep {
namespace Core {

ProjectItem::ProjectItem(const QString & typeId)
  : mId(QUuid::createUuid().toString())
  , mTypeId(typeId)
  , mParent(nullptr)
  , mProject(nullptr)
{
  setName(mTypeId);
}

ProjectItem::ProjectItem(const QString & typeId, const QString & name)
  : mId(QUuid::createUuid().toString())
  , mTypeId(typeId)
  , mParent(nullptr)
  , mProject(nullptr)
{
  setName(name);
}

void ProjectItem::addItem(ProjectItem * projectItem)
{
  mItems.append(projectItem);
  projectItem->setParent(this);
  projectItem->setProject(this->project());
  emit itemAdded(projectItem);
  if (mProject != nullptr) {
    mProject->setModified();
  }
}

ProjectItem * ProjectItem::findItem(const QString & itemId)
{
  for (int i = 0; i < mItems.size(); i++) {
    if (mItems.at(i)->id() == itemId) {
      return mItems.at(i);
    }
  }
  return nullptr;
}

const ProjectItem * ProjectItem::findItem(const QString & itemId) const
{
  for (int i = 0; i < mItems.size(); i++) {
    if (mItems.at(i)->id() == itemId) {
      return mItems.at(i);
    }
  }
  return nullptr;
}

QList<ProjectItem*> ProjectItem::findItems(const QString & name) const
{
  QList<ProjectItem*> items;
  for (int i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i);
    QString itemName = item->name();
    if (itemName == name) {
      items.append(item);
    }
  }
  return items;
}

QString ProjectItem::id() const
{
  return mId;
}

ProjectItem * ProjectItem::itemAt(int index)
{
  return mItems.at(index);
}

const ProjectItem * ProjectItem::itemAt(int index) const
{
  return mItems.at(index);
}

bool ProjectItem::loadChildren(QXmlStreamReader & reader)
{
  while (true) {
    bool success = reader.readNextStartElement();
    if (!success) {
      break;
    }

    // TODO: Need the factory here
    //QString elementName = reader.name().toString();
  }

  return !reader.hasError();
}

bool ProjectItem::loadXml(QXmlStreamReader & reader)
{
  QXmlStreamAttributes attrs = reader.attributes();
  if (attrs.hasAttribute("Name")) {
    QString name = attrs.value("Name").toString();
    setName(name);
  }

  loadAttributes(reader);
  loadChildren(reader);
  return !reader.hasError();
}

QString ProjectItem::name() const
{
  return mName;
}

ProjectItem * ProjectItem::parent() const
{
  return mParent;
}

Project * ProjectItem::project() const
{
  return mProject;
}

bool ProjectItem::removeItem(const QString & itemId)
{
  for (int i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i);
    if (item->id() == itemId) {
      emit itemAboutToBeRemoved(item);
      mItems.removeAt(i);
      emit itemRemoved();
      if (mProject != nullptr) {
        mProject->setModified();
      }
      return true;
    }
  }
  return false;
}

bool ProjectItem::saveChildren(QXmlStreamWriter & writer) const
{
  for (int i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i);
    item->saveXml(writer);
  }

  return !writer.hasError();
}

bool ProjectItem::saveXml(QXmlStreamWriter & writer) const
{
  writer.writeStartElement(mTypeId);
  saveAttributes(writer);
  saveChildren(writer);
  writer.writeEndElement();
  return !writer.hasError();
}

void ProjectItem::setName(const QString & name)
{
  mName = name;
  emit itemChanged();
  if (mProject != nullptr) {
    mProject->setModified();
  }
}

void ProjectItem::setProject(Project * project)
{
  mProject = project;
}

int ProjectItem::totalItems() const
{
  return mItems.size();
}

QString ProjectItem::typeId() const
{
  return mTypeId;
}

}
}
