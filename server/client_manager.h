#pragma once
#include <unordered_map>
#include <string>
#include <shared_mutex>

class ClientManager
{
public:
  bool add(const std::string &name, int client_socket_fd);
  void remove(const std::string &name);
  int get(const std::string &name);

private:
  std::shared_mutex shared_mutex_;
  std::unordered_map<std::string, int> name_to_socket_fd;
};