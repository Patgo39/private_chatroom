#ifndef USER_ADVICE_ENUM_H
#define USER_ADVICE_ENUM_H

#include <iostream>
#include <string>
#include <stdexcept>

enum class UserAdvice{
  NEW_USER,
    NEW_STATUS,
    USER_LIST,
    TEXT_FROM,
    PUBLIC_TEXT_FROM,
    JOINED_ROOM,
    ROOM_USER_LIST,
    ROOM_TEXT_FROM,
    LEFT_ROOM,
    DISCONNECTED
};

class UserAdviceEnum{
 public:
  static UserAdvice getUserAdviceFromString(std::string userAdvice);
};

#endif
