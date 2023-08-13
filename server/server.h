#include "client_manager.h"

class Server
{
public:
  Server(int port, int max_pending_connections);
  void start();

private:
  const int port;
  const int max_pending_connections;
  int server_socket_fd;
  ClientManager client_manager;

  void initialize_socket();
  void accept_connection();
  void handle_connection(int client_socket_fd);
  std::string register_name(int client_socket_fd);
  void process_client_inputs(int client_socket_fd, const std::string &name);
};