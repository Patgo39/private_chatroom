#ifndef OPERATION_ENUM_H
#define OPERATION_ENUM_H

#include <iostream>
#include <string>
#include <stdexcept>

class OperationEnum{
 public:
  enum Operation{
    IDENTIFY,
    STATUS,
    USERS,
    TEXT,
    NEW_ROOM,
    INVITE,
    JOIN_ROOM,
    ROOM_USERS,
    ROOM_TEXT,
    LEAVE_ROOM,
    DISCONNECT
  };

  static Operation getOperationFromString(std::string operation);
};

#endif
