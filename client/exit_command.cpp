#include "exit_command.h"
#include <sys/socket.h>

void ExitCommand::execute(Inbox &inbox, int socket_fd)
{
  shutdown(socket_fd, SHUT_RDWR);
  exit(EXIT_SUCCESS);
}