#include "operation.h"

/**
 * Dado un objeto Type se obtiene su equivalente en cadena.
 * @param type un objeto Type.
 * @return una cadena equivalente al objeto Type recibido.
 */
std::string Operation::getStringFromType(Type type){
  switch(type){
  case INVITE: return "INVITE";
  case JOIN_ROOM: return "JOIN_ROOM";
  case ROOM_USERS: return "ROOM_USERS";
  case ROOM_TEXT: return "ROOM_TEXT";
  case LEAVE_ROOM: return "LEAVE_ROOM";
  case TEXT: return "TEXT";
  default: std::abort(); // Nunca debería suceder.
  }
}
