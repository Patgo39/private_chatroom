#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <string>
#include <json/json.h>
#include <vector>
#include <sstream>
#include "command_exception.cpp"

class CommandManager{
  
 public:
  CommandManager();
  std::string getJsonFromCommand(std::string userMessage);

 private:
  std::vector<std::string> getCommandAsVector(std::string userMessage);
  std::string manageIdentification(std::vector<std::string> command);
  std::string manageNewStatus(std::vector<std::string> command);
  std::string manageUsersList(std::vector<std::string> command);
  std::string managePrivateMessage(std::vector<std::string> command);
  std::string manageNewRoom(std::vector<std::string> command);
  std::string manageInviteUsersToRoom(std::vector<std::string> command);
  std::string manageJoinRoom(std::vector<std::string> command);
  std::string manageRoomList(std::vector<std::string> command);
  std::string manageLeaveRoom(std::vector<std::string> command);
  std::string manageDisconnect(std::vector<std::string> command);
  std::string manageNormalText(std::string userMessage);

  std::string turnJsonToString(Json::Value json);
};

#endif
