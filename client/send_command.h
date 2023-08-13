#include "command.h"
#include "../message/message.h"

class SendCommand : public Command
{
public:
  SendCommand(const Message &message);
  virtual void execute(Inbox &inbox, int socket_fd);

private:
  const Message message;
};