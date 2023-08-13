#include <stdexcept>

class ClientNotFound : public std::runtime_error
{
public:
  ClientNotFound(const char *message) : std::runtime_error(message){};
};