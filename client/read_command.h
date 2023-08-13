#include "command.h"

class ReadCommand : public Command
{
public:
  virtual void execute(Inbox &inbox, int socket_fd);
};