#include "command.h"

class HelpCommand : public Command
{
public:
  virtual void execute(Inbox &inbox, int socket_fd);
};