#include <Exceptions/GLException.h>

GLException::GLException(const std::string &s) : message(s) {}

std::string GLException::GetMessage() const {
  return message;
}

std::ostream &operator<<(std::ostream &os, const GLException &e) {
  return os << e.GetMessage();
}

