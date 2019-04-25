#include "treeitem.h"

namespace Qtep {
namespace Gui {

TreeItem::TreeItem()
{
}

TreeItem::~TreeItem()
{
}

bool TreeItem::loadAttributes(QXmlStreamReader & streamReader)
{
  return streamReader.hasError();
}

bool TreeItem::loadFromXml(QXmlStreamReader & streamReader)
{
  loadAttributes(streamReader);
  return streamReader.hasError();
}

bool TreeItem::saveToXml(QXmlStreamWriter & streamWriter) const
{
  saveAttributes(streamWriter);
  return streamWriter.hasError();
}

bool TreeItem::saveAttributes(QXmlStreamWriter & streamWriter) const
{
  return streamWriter.hasError();
}

}
}
