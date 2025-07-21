#include <exception>
#include <iostream>
#include <string>

class InvalidOperationException : public std::exception{
  std::string message;

public:
  InvalidOperationException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
