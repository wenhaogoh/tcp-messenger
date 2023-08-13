#include "send_command.h"
#include "../exceptions/socket_exception.h"
#include <sys/socket.h>

SendCommand::SendCommand(const Message &message) : message(message) {}

void SendCommand::execute(Inbox &inbox, int socket_fd)
{
  std::string formatted_message = message.get_client_to_server_string();
  if (send(socket_fd, formatted_message.data(), formatted_message.size(), 0) < 0)
  {
    throw SocketException("Failed to send message");
  }
}