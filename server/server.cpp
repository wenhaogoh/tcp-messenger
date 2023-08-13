#include "../exceptions/socket_exception.h"
#include "server.h"
#include "parser.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

#define ERROR_MESSAGE "ERROR"
#define SUCCESS_MESSAGE "SUCCESS"

Server::Server(int port, int max_pending_connections) : port(port), max_pending_connections(max_pending_connections)
{
}

void Server::start()
{
  initialize_socket();
  while (true)
  {
    accept_connection();
  }
}

void Server::initialize_socket()
{
  if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    throw SocketException("Failed to create socket");
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(port);
  socklen_t address_len = sizeof(address);

  if (bind(server_socket_fd, (sockaddr *)&address, address_len) < 0)
  {
    throw SocketException("Failed to bind socket");
  }

  if (listen(server_socket_fd, max_pending_connections) < 0)
  {
    throw SocketException("Failed to listen on socket");
  }
  std::cout << "Server listening on port " << port << "\n";
}

void Server::accept_connection()
{
  sockaddr_in address;
  socklen_t address_len = sizeof(address);
  int client_socket_fd;
  if ((client_socket_fd = accept(server_socket_fd, (sockaddr *)&address, &address_len)) < 0)
  {
    throw SocketException("Failed to accept incoming connection");
  }
  std::thread thread_(&Server::handle_connection, this, client_socket_fd);
  thread_.detach();
}

void Server::handle_connection(int client_socket_fd)
{
  try
  {
    std::string name = register_name(client_socket_fd);
    process_client_inputs(client_socket_fd, name);
  }
  catch (const SocketException &e)
  {
    std::cout << e.what();
  }
}

std::string Server::register_name(int client_socket_fd)
{
  std::vector<char> name_buffer(50);
  while (true)
  {
    ssize_t name_len = recv(client_socket_fd, name_buffer.data(), name_buffer.size(), 0);
    if (name_len < 0)
    {
      throw SocketException("Failed to receive incoming name");
    }
    else if (name_len == 0)
    {
      throw SocketException("Connection closed when registering name\n");
    }
    std::string name = name_buffer.data();
    if (!client_manager.add(name, client_socket_fd))
    {
      if (send(client_socket_fd, ERROR_MESSAGE, sizeof(ERROR_MESSAGE), 0) < 0)
      {
        throw SocketException("Failed to send error message");
      };
      continue;
    }
    if (send(client_socket_fd, SUCCESS_MESSAGE, sizeof(SUCCESS_MESSAGE), 0) < 0)
    {
      throw SocketException("Failed to send success message");
    };
    break;
  }
  std::cout << name_buffer.data() << " joined\n";
  return name_buffer.data();
}

void Server::process_client_inputs(int client_socket_fd, const std::string &name)
{
  std::vector<char> input_buffer(150);
  while (true)
  {
    ssize_t input_len = recv(client_socket_fd, input_buffer.data(), input_buffer.size(), 0);
    if (input_len < 0)
    {
      throw SocketException("Failed to receive incoming input");
    }
    if (input_len == 0)
    {
      client_manager.remove(name);
      std::string error_message = name + " left\n";
      throw SocketException(error_message.data());
    }
    Parser::parse(input_buffer.data(), name)->execute(client_manager);
  }
}