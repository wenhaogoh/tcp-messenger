#include "read_command.h"
#include <iostream>

void ReadCommand::execute(Inbox &inbox, int socket_fd)
{
  std::vector<Message> messages = inbox.read();
  if (messages.empty())
  {
    std::cout << "You do not have any messages currently\n";
    return;
  }
  for (auto &message : messages)
  {
    std::cout << message.get_client_display_string() << "\n";
  }
}