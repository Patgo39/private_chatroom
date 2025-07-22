/**
 * @class NoSuchUserInRoomException
 * @brief Excepción lanzada cuando un usuario no se encuentra en un cuarto.
 *
 * Esta excepción se utiliza cuando un cliente intenta realizar una operación 
 * relacionada con otro usuario dentro de un cuarto, pero ese usuario no está 
 * presente en la lista de usuarios del cuarto o no existe en absoluto.
 */

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
