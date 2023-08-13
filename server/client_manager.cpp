#include "client_manager.h"
#include "../exceptions/client_not_found_exception.h"

bool ClientManager::add(const std::string &name, int client_socket_fd)
{
  std::unique_lock lock(shared_mutex_);
  if (name_to_socket_fd.count(name))
  {
    return false;
  }
  name_to_socket_fd[name] = client_socket_fd;
  return true;
}

void ClientManager::remove(const std::string &name)
{
  std::unique_lock lock(shared_mutex_);
  name_to_socket_fd.erase(name);
}

int ClientManager::get(const std::string &name)
{
  std::shared_lock lock(shared_mutex_);
  if (name_to_socket_fd.count(name) == 0)
  {
    throw ClientNotFound("Target client not connected");
  }
  return name_to_socket_fd[name];
}