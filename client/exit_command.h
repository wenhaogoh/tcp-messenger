#include "command.h"

class ExitCommand : public Command
{
public:
  virtual void execute(Inbox &inbox, int socket_fd);
};