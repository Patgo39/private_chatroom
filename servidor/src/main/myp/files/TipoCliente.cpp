#include "TipoCliente.h"

std::string TipoCliente::getString(TipoCliente::Tipo tipo){
  switch(tipo){
  case IDENTIFY: return "IDENTIFY"; break;
  case STATUS: return "STATUS"; break;
  case USERS: return "USERS"; break;
  case TEXT: return "TEXT"; break;
  case PUBLIC_TEXT: return "PUBLIC_TEXT"; break;
  case NEW_ROOM: return "NEW_ROOM"; break;
  case INVITE: return "INVITE"; break;
  case JOIN_ROOM: return "JOIN_ROOM"; break;
  case ROOM_USERS: return "ROOM_USERS"; break;
  case ROOM_TEXT: return "ROOM_TEXT"; break;
  case LEAVE_ROOM: return "LEAVE_ROOM"; break;
  case DISCONNECT: return "DISCONNECT"; break;
  }
}

int TipoCliente::getTipo(std::string tipo){
  if(tipo == "IDENTIFY"){
    return IDENTIFY;
  }else if(tipo == "STATUS"){
    return STATUS;
  }else if(tipo == "USERS"){
    return USERS;
  }else if(tipo == "TEXT"){
    return TEXT;
  }else if(tipo == "PUBLIC_TEXT"){
    return PUBLIC_TEXT;
  }else if(tipo == "NEW_ROOM"){
    return NEW_ROOM;
  }else if(tipo == "INVITE"){
    return INVITE;
  }else if(tipo == "JOIN_ROOM"){
    return JOIN_ROOM;
  }else if(tipo == "ROOM_USERS"){
    return ROOM_USERS;
  }else if(tipo == "ROOM_TEXT"){
    return ROOM_TEXT;
  }else if(tipo == "LEAVE_ROOM"){
    return LEAVE_ROOM;
  }else if(tipo == "DISCONNECT"){
    return DISCONNECT;
  }else{
    return 0;
  }
}
