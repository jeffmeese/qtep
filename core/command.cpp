#include "command.h"

namespace Qtep {
namespace Core {

Command::Command(const QString & id)
  : mId(id)
{
}

QString Command::commandId() const
{
  return mId;
}

void Command::redo()
{
  execute();
}

void Command::undo()
{
  unexecute();
}

}
}
