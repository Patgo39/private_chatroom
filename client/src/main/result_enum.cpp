#include "result_enum.h"

ResultEnum::Result ResultEnum::getResultFromString(std::string result) {
  if (result == "USER_ALREADY_EXISTS") return USER_ALREADY_EXISTS;
  if (result == "NO_SUCH_USER") return NO_SUCH_USER;
  if (result == "ROOM_ALREADY_EXISTS") return ROOM_ALREADY_EXISTS;
  if (result == "NO_SUCH_ROOM") return NO_SUCH_ROOM;
  if (result == "NOT_INVITED") return NOT_INVITED;
  if (result == "NOT_JOINED") return NOT_JOINED;
  if (result == "NAME_TOO_LONG") return NAME_TOO_LONG;
  
  throw std::invalid_argument("Unknown result: " + result);
}
