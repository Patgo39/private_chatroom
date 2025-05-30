#ifndef OPERATION_H
#define OPERATION_h

#include <iostream>
#include <string>

class Operation{
 public:
  enum Type{
    INVITE = 1,
    JOIN_ROOM = 2,
    ROOM_USERS = 3,
    ROOM_TEXT = 4,
    LEAVE_ROOM = 5,
    TEXT = 6
  };
  
  static std::string getStringFromType(Type type);
};

#endif
