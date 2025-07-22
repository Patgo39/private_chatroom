#include "user_status.h"

/**
 * Regresa la cadena dado un objeto status.
 * @param status un objeto de la enumeración status.
 * @return su equivalente a cadena del tipo status.
 */
std::string UserStatus::getString(UserStatus::Status status){
  switch(status){
  case ACTIVE: return "ACTIVE"; 
  case BUSY: return "BUSY";
  case AWAY: return "AWAY";
    
  }
  // Es inecesario, pero se evita una advertencia al regresar una cadena vacía.
  return "";
}

/**
 * Dada una cadena se regresa un objeto de la enumeración status. Si tal cadena
 * no tiene su equivalente, por defecto regresa un estado de tipo ACTIVE.
 * @param status una cadena equivalente a un valor de la enumeración status.
 * @return un objeto de tipo status.
 */
UserStatus::Status UserStatus::getStatusFromString(std::string status){

  for(char &c:status){
    c = std::toupper(c);
  }
  
  if (status == "ACTIVE"){
    return UserStatus::Status::ACTIVE;
  }else if(status == "BUSY"){
    return UserStatus::Status::BUSY;
  }else if(status == "AWAY"){
    return UserStatus::Status::AWAY;
  }

  return UserStatus::Status::ACTIVE;
}
