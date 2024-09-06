#include "TipoCliente.h"

std::string TipoCliente::getString(TipoCliente::Tipo tipo){
  switch(tipo){
  case IDENTIFY: return "IDENTIFY"; break;
  case STATUS: return "STATUS"; break;
  case USERS: return "USERS"; break;
  case TEXT: return "TEXT"; break;
  case PUBLIC_TEX: return "PUBLIC_TEX"; break;
  case NEW_ROOM: return "NEW_ROOM"; break;
  case INVITE: return "INVITE"; break;
  case JOIN_ROOM: return "JOIN_ROOM"; break;
  case ROOM_USERS: return "ROOM_USERS"; break;
  case ROOM_TEXT: return "ROOM_TEXT"; break;
  case LEAVE_ROOM: return "LEAVE_ROOM"; break;
  case DISCONNECT: return "DISCONNECT"; break;
  }
}
