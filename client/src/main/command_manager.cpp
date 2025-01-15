#include "command_manager.h"

CommandManager::CommandManager(){

}

std::string CommandManager::getJsonFromCommand(std::string userMessage){
  std::vector<std::string> command = getCommandAsVector(userMessage);

  if(command[0] == "/chat"){
    
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
}

std::string CommandManager::turnJsonToString(Json::Value json){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, json);
  return output;
}
