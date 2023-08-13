#include <stdexcept>

class ParseException : public std::runtime_error
{
public:
  ParseException(const char *message) : std::runtime_error(message){};
};