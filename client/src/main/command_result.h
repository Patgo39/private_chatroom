#ifndef COMMAND_RESULT_H
#define COMMAND_RESULT_H

#include <string>

struct CommandResult{
  std::string output;
  bool ownMessage;
  bool stillConnected;
  bool leaveRoom;
  std::string roomToLeave;
};

#endif
