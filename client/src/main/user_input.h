#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <string>
#include <iostream>
#include <stdexcept>

class UserInput{
  bool input_in_main_room;
  std::string roomName;
  std::string input;
 public:
  UserInput();
  void buildGeneralRoomInput(std::string msg);
  void buildPrivateRoomInput(std::string msg, std::string room);
  
  std::string getInput();
  std::string getRoomName();
  bool isInputFromMainRoom();
};

#endif
