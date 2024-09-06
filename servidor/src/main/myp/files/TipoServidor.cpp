#include "TipoServidor.h"

std::string TipoServidor::getString(TipoServidor::Tipo tipo){
  switch(tipo){
  case RESPONSE: return "RESPONSE"; break;
  case NEW_USER: return "NEW_USER"; break;
  case NEW_STATUS: return "NEW_STATUS"; break;
  case USER_LIST: return "USER_LIST"; break;
  case TEXT_FROM: return "TEXT_FROM"; break;
  case PUBLIC_TEXT_FROM: return "PUBLIC_TEXT_FROM"; break;
  case JOINED_ROOM: return "JOINED_ROOM"; break;
  case ROOM_USER_LIST: return "ROOM_USER_LIST"; break;
  case ROOM_TEXT_FROM: return "ROOM_TEXT_FROM"; break;
  case LEFT_ROOM: return "LEFT_ROOM"; break;
  case DISCONNECTED: return "DISCONNECTED"; break;
  };
  return "NULL";
}
