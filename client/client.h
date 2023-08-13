#include "inbox.h"

class Client
{
public:
  void start();

private:
  int socket_fd;
  std::string name;
  Inbox inbox;

  void initialize_socket();
  void register_name();
  void process_server_inputs();
  void process_server_inputs_handler();
  void process_client_inputs();
};