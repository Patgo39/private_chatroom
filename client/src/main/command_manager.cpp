#include "command_manager.h"

CommandManager::CommandManager(){

}

std::string CommandManager::getJsonFromCommand(std::string userMessage){
  std::vector<std::string> command = getCommandAsVector(userMessage);

  if(command[0] == "REQ"){
    
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
