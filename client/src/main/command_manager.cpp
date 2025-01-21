#include "command_manager.h"

CommandManager::CommandManager(){

}

std::string CommandManager::getJsonFromCommand(std::string userMessage){
  std::vector<std::string> command = getCommandAsVector(userMessage);

  if(command[0] == "/identify"){
    return manageIdentification(command);
    
  }else if(command[0] == "/status"){
    
  }else if(command[0] == "/list"){
    
  }else if(command[0] == "/private"){
    
  }else if(command[0] == "/newroom"){
    
  }else if(command[0] == "/invite"){
    
  }else if(command[0] == "/join"){
    
  }else if(command[0] == "/roomlist"){
    
  }else if(command[0] == "/leave"){
    
  }else if(command[0] == "/disconnect"){
    
  }else{
    return manageNormalText(userMessage);
  }
  
}

std::vector<std::string> CommandManager::getCommandAsVector(std::string userMessage){
  std::vector<std::string> command;
  std::string temp;
  std::stringstream ss(userMessage);

  while(getline(ss, temp, ' ')){
    command.push_back(temp);
  }
  return command;
}

std::string CommandManager::manageNormalText(std::string userMessage){
  Json::Value json;
  json["type"] = "PUBLIC_TEXT";
  json["text"] = userMessage;

  return turnJsonToString(json);
}

std::string CommandManager::turnJsonToString(Json::Value json){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, json);
  return output;
}

std::string CommandManager::manageIdentification(std::vector<std::string> command){

}

std::string CommandManager::manageNewStatus(std::vector<std::string> command){

}

std::string CommandManager::manageUsersList(std::vector<std::string> command){

}

std::string CommandManager::managePrivateMessage(std::vector<std::string> command){

}

std::string CommandManager::manageNewRoom(std::vector<std::string> command){

}

std::string CommandManager::manageInviteUsersToRoom(std::vector<std::string> command){

}

std::string CommandManager::manageJoinRoom(std::vector<std::string> command){

}

std::string CommandManager::manageRoomList(std::vector<std::string> command){

}

std::string CommandManager::manageLeaveRoom(std::vector<std::string> command){

}

std::string CommandManager::manageDisconnect(std::vector<std::string> command){

}

