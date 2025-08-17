#include "user_advice_enum.h"

UserAdvice UserAdviceEnum::getUserAdviceFromString(std::string userAdvice){
  if (userAdvice == "NEW_USER")         return UserAdvice::NEW_USER;
  if (userAdvice == "NEW_STATUS")       return UserAdvice::NEW_STATUS;
  if (userAdvice == "USER_LIST")        return UserAdvice::USER_LIST;
  if (userAdvice == "TEXT_FROM")        return UserAdvice::TEXT_FROM;
  if (userAdvice == "PUBLIC_TEXT_FROM") return UserAdvice::PUBLIC_TEXT_FROM;
  if (userAdvice == "INVITATION")       return UserAdvice::INVITATION;
  if (userAdvice == "JOINED_ROOM")      return UserAdvice::JOINED_ROOM;
  if (userAdvice == "ROOM_USER_LIST")   return UserAdvice::ROOM_USER_LIST;
  if (userAdvice == "ROOM_TEXT_FROM")   return UserAdvice::ROOM_TEXT_FROM;
  if (userAdvice == "LEFT_ROOM")        return UserAdvice::LEFT_ROOM;
  if (userAdvice == "DISCONNECTED")     return UserAdvice::DISCONNECTED;
  
  throw std::invalid_argument("Unknown UserAdvice: " + userAdvice);
}
