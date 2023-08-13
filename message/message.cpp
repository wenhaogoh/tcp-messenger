#include "message.h"

std::string Message::get_server_to_client_string() const
{
  return "MESSAGE " + from + " " + message;
}

std::string Message::get_client_to_server_string() const
{
  return "MESSAGE " + to + " " + message;
}

std::string Message::get_client_display_string() const
{
  return from + ": " + message;
}