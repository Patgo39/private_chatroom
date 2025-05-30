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
  static std::string getString(UserStatus::Status status);
  static UserStatus::Status getStatusFromString(std::string status);
};

#endif
