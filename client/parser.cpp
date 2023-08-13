#include "../exceptions/parse_exception.h"
#include "exit_command.h"
#include "parser.h"
#include "read_command.h"
#include "receive_command.h"
#include "send_command.h"
#include "help_command.h"
#include <iostream>

const std::string Parser::delim = " ";

std::unique_ptr<Command> Parser::parse_server_input(const std::string &input, const std::string &name)
{
  size_t start = 0;
  size_t end = input.find(delim, start);
  std::string command_type = input.substr(start, end - start);
  if (command_type == "MESSAGE")
  {
    start = end + delim.size();
    end = input.find(delim, start);
    std::string from = input.substr(start, end - start);

    start = end + delim.size();
    std::string message = input.substr(start);
    return std::unique_ptr<Command>(new ReceiveCommand({from, name, message}));
  }
  throw ParseException("Unable to parse badly formed server input");
}

std::unique_ptr<Command> Parser::parse_client_input(const std::string &input, const std::string &name)
{
  size_t start = 0;
  size_t end = input.find(delim, start);
  std::string command_type = input.substr(start, end - start);
  if (command_type == "MESSAGE")
  {
    start = end + delim.size();
    end = input.find(delim, start);
    std::string to = input.substr(start, end - start);

    start = end + delim.size();
    std::string message = input.substr(start);
    return std::unique_ptr<Command>(new SendCommand({name, to, message}));
  }
  if (command_type == "READ")
  {
    return std::unique_ptr<Command>(new ReadCommand());
  }
  if (command_type == "EXIT")
  {
    return std::unique_ptr<Command>(new ExitCommand());
  }
  return std::unique_ptr<Command>(new HelpCommand());
}