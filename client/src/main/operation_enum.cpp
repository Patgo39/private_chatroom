#include "operation_enum.h"

OperationEnum::Operation OperationEnum::getOperationFromString(std::string operation){
  if (operation == "IDENTIFY") return Operation::IDENTIFY;
    if (operation == "STATUS") return Operation::STATUS;
    if (operation == "USERS") return Operation::USERS;
    if (operation == "TEXT") return Operation::TEXT;
    if (operation == "NEW_ROOM") return Operation::NEW_ROOM;
    if (operation == "INVITE") return Operation::INVITE;
    if (operation == "JOIN_ROOM") return Operation::JOIN_ROOM;
    if (operation == "ROOM_USERS") return Operation::ROOM_USERS;
    if (operation == "ROOM_TEXT") return Operation::ROOM_TEXT;
    if (operation == "LEAVE_ROOM") return Operation::LEAVE_ROOM;
    if (operation == "DISCONNECT") return Operation::DISCONNECT;

    throw std::invalid_argument("Unknown operation: " + operation);
}
