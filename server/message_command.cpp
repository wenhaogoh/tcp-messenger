#include "message_command.h"
#include <sys/socket.h>
#include "../exceptions/socket_exception.h"

MessageCommand::MessageCommand(const std::string &from, const std::string &to, const std::string &message) : message({from, to, message})
{
}

void MessageCommand::execute(ClientManager &client_manager)
{
  std::string formatted_message = message.get_server_to_client_string();
  int to_socket_fd = client_manager.get(message.to);
  if (send(to_socket_fd, formatted_message.data(), formatted_message.length(), 0) < 0)
  {
    throw SocketException("Failed to send message");
  }
}