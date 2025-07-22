#ifndef OPERATION_H
#define OPERATION_h

#include <iostream>
#include <string>

class Operation{
 public:
  // Enumeración con el tipo de operación.
  enum Type{
    INVITE = 1,
    JOIN_ROOM = 2,
    ROOM_USERS = 3,
    ROOM_TEXT = 4,
    LEAVE_ROOM = 5,
    TEXT = 6
  };

  // Dado un objeto Type se obtiene su equivalente en cadena.
  static std::string getStringFromType(Type type);
};

#endif
