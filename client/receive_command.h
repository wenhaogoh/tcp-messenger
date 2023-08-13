#include "command.h"
#include "../message/message.h"

class ReceiveCommand : public Command
{
public:
  ReceiveCommand(const Message &message);
  virtual void execute(Inbox &inbox, int socket_fd);

private:
  const Message message;
};