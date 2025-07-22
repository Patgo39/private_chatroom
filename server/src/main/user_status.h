#ifndef USERSTATUS_H
#define USERSTATUS_H

#include <iostream>
#include <string>
class UserStatus{
public:
  enum Status{
    ACTIVE = 1,
    BUSY = 2,
    AWAY = 3
  };
  // Regresa la cadena dado un objeto de la enumeracion status.
  static std::string getString(UserStatus::Status status);
  // Dada una cadena regresa un objeto de la enumeración status.
  static UserStatus::Status getStatusFromString(std::string status);
};

#endif
