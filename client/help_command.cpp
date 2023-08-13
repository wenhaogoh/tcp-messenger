#include "help_command.h"
#include <iostream>

void HelpCommand::execute(Inbox &inbox, int socket_fd)
{
  std::cout << "Unrecognised command. Available commands: MESSAGE <NAME> <CONTENT>, READ, EXIT\n";
}