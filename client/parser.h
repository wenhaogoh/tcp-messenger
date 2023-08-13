#include "command.h"
#include <memory>
#include <vector>

class Parser
{
public:
  static std::unique_ptr<Command> parse_client_input(const std::string &input, const std::string &name);
  static std::unique_ptr<Command> parse_server_input(const std::string &input, const std::string &name);

private:
  static const std::string delim;
};