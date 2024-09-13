#include "TipoServidor.h"

std::string TipoServidor::getString(TipoServidor::Tipo tipo){
  switch(tipo){
  case RESPONSE: return "RESPONSE"; 
  case NEW_USER: return "NEW_USER";
  case NEW_STATUS: return "NEW_STATUS"; 
  case USER_LIST: return "USER_LIST"; 
  case TEXT_FROM: return "TEXT_FROM"; 
  case PUBLIC_TEXT_FROM: return "PUBLIC_TEXT_FROM"; 
  case JOINED_ROOM: return "JOINED_ROOM"; 
  case ROOM_USER_LIST: return "ROOM_USER_LIST"; 
  case ROOM_TEXT_FROM: return "ROOM_TEXT_FROM";
  case LEFT_ROOM: return "LEFT_ROOM";
  case DISCONNECTED: return "DISCONNECTED";
  case INVALID: return "INVALID";
  case INVITATION: return "INVITATION";
  };
  return "NULL";
}
