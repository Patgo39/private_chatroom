#ifndef RESULT_ENUM_H
#define RESULT_ENUM_H

#include <iostream>
#include <string>
#include <stdexcept>

enum Result{
    USER_ALREADY_EXISTS,
    NO_SUCH_USER,
    ROOM_ALREADY_EXISTS,
    NO_SUCH_ROOM,
    NOT_INVITED,
    NOT_JOINED,
    NAME_TOO_LONG,
};

class ResultEnum{
 public:

  static Result getResultFromString(std::string result);
};


#endif
