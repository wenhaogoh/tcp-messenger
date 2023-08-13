#include "command.h"
#include <memory>
#include <vector>

class Parser
{
public:
  static std::unique_ptr<Command> parse(const std::string &input, const std::string &from);

private:
  static const std::string delim;
};