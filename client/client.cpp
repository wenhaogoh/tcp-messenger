#include "../exceptions/socket_exception.h"
#include "client.h"
#include "parser.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

#define ERROR_MESSAGE "ERROR"
#define SUCCESS_MESSAGE "SUCCESS"

void Client::start()
{
  initialize_socket();
  register_name();
  process_server_inputs();
  process_client_inputs();
}

void Client::initialize_socket()
{
  std::cout << "Please enter server port number: ";
  std::string input;
  getline(std::cin, input);
  int port = stoi(input);

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    throw SocketException("Failed to create socket");
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(port);
  socklen_t address_len = sizeof(address);

  if (connect(socket_fd, (sockaddr *)&address, address_len) < 0)
  {
    throw SocketException("Failed to connect socket");
  }
  std::cout << "Connected to server\n";
}

void Client::register_name()
{
  while (true)
  {
    std::cout << "Please enter your name: ";
    getline(std::cin, name);
    // TODO: check that name is one word
    if (send(socket_fd, name.data(), name.size(), 0) < 0)
    {
      throw SocketException("Failed to send name");
    }
    std::vector<char> response_buffer(50);
    if (recv(socket_fd, response_buffer.data(), response_buffer.size(), 0) < 0)
    {
      throw SocketException("Failed to receive response");
    }
    std::string response = response_buffer.data();
    if (response == ERROR_MESSAGE)
    {
      std::cout << "Name already in use, please try again\n";
      continue;
    }
    if (response == SUCCESS_MESSAGE)
    {
      std::cout << "Registration successful\n";
      break;
    }
    throw SocketException("Unknown response");
  }
}

void Client::process_server_inputs()
{
  std::thread thread_(&Client::process_server_inputs_handler, this);
  thread_.detach();
}

void Client::process_server_inputs_handler()
{
  while (true)
  {
    std::vector<char> input_buffer(150);
    ssize_t input_len = recv(socket_fd, input_buffer.data(), input_buffer.size(), 0);
    if (input_len == 0)
    {
      break;
    }
    if (input_len < 0)
    {
      throw SocketException("Failed to receive server input");
    }
    Parser::parse_server_input(input_buffer.data(), name)->execute(inbox, socket_fd);
  }
}

void Client::process_client_inputs()
{
  std::string input;
  while (true)
  {
    std::cout << "Enter command: ";
    getline(std::cin, input);
    Parser::parse_client_input(input, name)->execute(inbox, socket_fd);
  }
}