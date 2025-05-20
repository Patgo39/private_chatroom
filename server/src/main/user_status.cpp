#include "user_status.h"

std::string UserStatus::getString(UserStatus::Status status){
  switch(status){
  case ACTIVE: return "ACTIVE"; 
  case BUSY: return "BUSY";
  case AWAY: return "AWAY";
  }
  return "NULL";
}

