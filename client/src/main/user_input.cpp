#include "user_input.h"

UserInput::UserInput(){
}

void UserInput::buildGeneralRoomInput(std::string msg){
  input_in_main_room = true;
  input = msg;
}

void UserInput::buildPrivateRoomInput(std::string msg, std::string room){
  input_in_main_room = false;
  roomName = room;
  input = msg;
}

std::string UserInput::getInput(){
  return input;
}

std::string UserInput::getRoomName(){
  if(input_in_main_room){
    throw std::runtime_error("Access to roomname denied. The input was in the main room.");
  }
  return roomName;
}

bool UserInput::isInputFromMainRoom(){
  return input_in_main_room;
}

