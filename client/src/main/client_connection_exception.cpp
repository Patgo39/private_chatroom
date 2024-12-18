
#include <exception>
#include <iostream>
#include <string>

class ClientConnectionException : public std::exception {
  std::string message;

public:

  ClientConnectionException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
