#include "ResultadoServidor.h"

std::string ResultadoServidor::getString(ResultadoServidor::Resultado resultado){
  switch(resultado){
  case SUCCESS: return "SUCCESS"; break;
  case USER_ALREADY_EXISTS: return "USER_ALREADY_EXISTS"; break;
  case NO_SUCH_USER: return "NO_SUCH_USER"; break;
  case ROOM_ALREADY_EXISTS: return "ROOM_ALREADY_EXISTS"; break;
  case NO_SUCH_ROOM: return "NO_SUCH_ROOM"; break; 
  case NOT_INVITED: return "NOT_INVITED"; break;
  case NOT_JOINED: return "NOT_JOINED"; break;
  }
  return "NULL";
}
