#include <exception>
#include <iostream>
#include <string>

class NoSuchUserInRoomException : public std::exception {
  std::string message;

public:
  NoSuchUserInRoomException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
