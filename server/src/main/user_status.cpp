#include "user_status.h"

std::string UserStatus::getString(UserStatus::Status status){
  switch(status){
  case ACTIVE: return "ACTIVE"; 
  case BUSY: return "BUSY";
  case AWAY: return "AWAY";
  }
  return "NULL";
}

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
