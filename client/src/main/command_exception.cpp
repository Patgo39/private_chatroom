#include <exception>
#include <iostream>
#include <string>

class CommandException : public std::exception {
  std::string message;

public:

  CommandException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
