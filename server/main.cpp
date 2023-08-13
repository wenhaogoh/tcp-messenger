#include <string>
#include "server.h"

int main(int argc, const char *argv[])
{
  int port = std::stoi(argv[1]);
  int max_pending_connections = std::stoi(argv[2]);
  Server server(port, max_pending_connections);
  server.start();
}