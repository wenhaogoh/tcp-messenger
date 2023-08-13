#include "receive_command.h"

ReceiveCommand::ReceiveCommand(const Message &message) : message(message) {}

void ReceiveCommand::execute(Inbox &inbox, int socket_fd)
{
  inbox.add(message);
}