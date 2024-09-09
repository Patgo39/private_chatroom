#include "ResultadoServidor.h"

std::string ResultadoServidor::getString(ResultadoServidor::Resultado resultado){
  switch(resultado){
  case SUCCESS: return "SUCCESS"; 
  case USER_ALREADY_EXISTS: return "USER_ALREADY_EXISTS"; 
  case NO_SUCH_USER: return "NO_SUCH_USER"; 
  case ROOM_ALREADY_EXISTS: return "ROOM_ALREADY_EXISTS";
  case NO_SUCH_ROOM: return "NO_SUCH_ROOM"; 
  case NOT_INVITED: return "NOT_INVITED";
  case NOT_JOINED: return "NOT_JOINED"; 
  }
  return "NULL";
}
