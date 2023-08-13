#include "parser.h"
#include "message_command.h"
#include "../exceptions/parse_exception.h"
#include <iostream>

const std::string Parser::delim = " ";

std::unique_ptr<Command> Parser::parse(const std::string &input, const std::string &from)
{
  size_t start = 0;
  size_t end = input.find(delim, start);
  std::string command_type = input.substr(start, end - start);
  if (command_type == "MESSAGE") // MESSAGE <TO> <CONTENT>
  {
    start = end + delim.size();
    end = input.find(delim, start);
    std::string to = input.substr(start, end - start);

    start = end + delim.size();
    std::string message = input.substr(start);
    return std::unique_ptr<Command>(new MessageCommand(from, to, message));
  }
  throw ParseException("Unable to parse badly formed client input");
}