#include "command.h"
#include "../message/message.h"

class MessageCommand : public Command
{
public:
  MessageCommand(const std::string &from, const std::string &to, const std::string &message);
  virtual void execute(ClientManager &client_manager);

private:
  Message message;
};