#ifndef GL_EXCEPTION_H
#define GL_EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

class GLException : public std::exception {
 protected:
  std::string message;
 public:
  explicit GLException(const std::string &s);
  virtual std::string GetMessage() const;
};

std::ostream &operator<<(std::ostream &os, const GLException &e);

#endif //GL_EXCEPTION_H

