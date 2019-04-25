#ifndef COMMAND_H
#define COMMAND_H

#include "qtep.h"

#include <QUndoCommand>

namespace Qtep {
namespace Core {

class Command
    : public QUndoCommand
{
public:
  QTEP_LIB_DECL QString commandId() const;

public:
  QTEP_LIB_DECL virtual void redo() override;
  QTEP_LIB_DECL virtual void undo() override;

protected:
  Command(const QString & id);
  Command(const Command & command) = delete;
  Command & operator=(const Command & command) = delete;

protected:
  virtual void execute() = 0;
  virtual void unexecute() = 0;

private:
  QString mId;
};

}
}

#endif // COMMAND_H
