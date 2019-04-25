#include "project.h"
#include "projectitem.h"

#include <QFile>
#include <QDebug>

namespace Qtep {
namespace Core {

Project::Project()
  : mModified(false)
  , mName("Project")
{
}

void Project::addItem(ProjectItem * projectItem)
{
  mItems.append(projectItem);
  projectItem->setProject(this);
  emit itemAdded(projectItem);
  setModified();
}

QString Project::fileName() const
{
  return mFileName;
}

ProjectItem * Project::findItem(const QString & itemId)
{
  for (int i = 0; i < mItems.size(); i++) {
    if (mItems.at(i)->id() == itemId) {
      return mItems.at(i);
    }
  }
  return nullptr;
}

const ProjectItem * Project::findItem(const QString & itemId) const
{
  for (int i = 0; i < mItems.size(); i++) {
    if (mItems.at(i)->id() == itemId) {
      return mItems.at(i);
    }
  }
  return nullptr;
}

QList<ProjectItem*> Project::findItems(const QString & name) const
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

ProjectItem * Project::itemAt(int index)
{
  return mItems.at(index);
}

const ProjectItem * Project::itemAt(int index) const
{
  return mItems.at(index);
}

bool Project::load(const QString & fileName)
{
  mFileName = QString();

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly)) {
    return false;
  }

  QXmlStreamReader reader(&file);
  if (!loadXml(reader)) {
    return false;
  }

  mFileName = fileName;
  setModified(false);
  return true;
}

bool Project::loadXml(QXmlStreamReader & reader)
{
  return !reader.hasError();
}

bool Project::modified() const
{
  return mModified;
}

QString Project::name() const
{
  return mName;
}

void Project::newProject()
{
  mName = QString();
  mFileName = QString();
  mItems.clear();
  setModified(false);
}

bool Project::removeItem(const QString & itemId)
{
  for (int i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i);
    if (item->id() == itemId) {
      emit itemAboutToBeRemoved(item);
      mItems.removeAt(i);
      emit itemRemoved();
      setModified();
      return true;
    }
  }
  return false;
}

bool Project::save(const QString & fileName)
{
  mFileName = QString();

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly)) {
    return false;
  }

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.writeStartDocument();
  if (!saveXml(writer)) {
    return false;
  }
  writer.writeEndDocument();

  mFileName = fileName;
  setModified(false);
  return true;
}

bool Project::saveXml(QXmlStreamWriter & writer) const
{
  writer.writeStartElement("Project");
  for (int i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i);
    item->saveXml(writer);
  }
  writer.writeEndElement();
  return !writer.hasError();
}

void Project::setModified(bool value)
{
  mModified = value;
  emit modified(value);
}

void Project::setName(const QString & name)
{
  qDebug() << QObject::tr(__FUNCTION__);

  mName = name;
  emit nameChanged(name);
  setModified();
}

int Project::totalItems() const
{
  return mItems.size();
}

}
}
