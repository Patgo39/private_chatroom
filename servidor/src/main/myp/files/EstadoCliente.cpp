#include "EstadoCliente.h"

std::string EstadoCliente::getString(EstadoCliente::Estado estado){
  switch(estado){
  case ACTIVE: return "ACTIVE"; 
  case BUSY: return "BUSY";
  case AWAY: return "AWAY";
  }
  
}
