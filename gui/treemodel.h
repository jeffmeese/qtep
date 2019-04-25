#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "qtep.h"

#include <QAbstractItemModel>

namespace Qtep {
namespace Gui {

class TreeModel
    : public QAbstractItemModel
{
public:
  QTEP_LIB_DECL TreeModel();
  QTEP_LIB_DECL virtual ~TreeModel();
};

}
}

#endif // TREEMODEL_H
