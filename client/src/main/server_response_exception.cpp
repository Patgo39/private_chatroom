#include <exception>
#include <iostream>
#include <string>

class ServerResponseException : public std::exception {
  std::string message;

public:
  ServerResponseException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
