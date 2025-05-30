#include "operation.h"

std::string Operation::getStringFromType(Type type){
  switch(type){
  case INVITE: return "INVITE";
  case JOIN_ROOM: return "JOIN_ROOM";
  case ROOM_USERS: return "ROOM_USERS";
  case ROOM_TEXT: return "ROOM_TEXT";
  case LEAVE_ROOM: return "LEAVE_ROOM";
  case TEXT: return "TEXT";
  }
}
