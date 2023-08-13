#pragma once
#include <string>

struct Message
{
  const std::string from;
  const std::string to;
  const std::string message;

  std::string get_server_to_client_string() const;
  std::string get_client_to_server_string() const;
  std::string get_client_display_string() const;
};