#include "command_manager.h"

CommandManager::CommandManager(){

}

std::string CommandManager::getJsonFromCommand(std::string userMessage, bool &stillConnected){
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
    stillConnected = false;
    return manageDisconnect();
    
  }else if(command[0][0] == '/'){
    std::string e = "Command " + command[0] + " doesn't exists.";
    throw CommandException(e.c_str());
    
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

  std::vector<std::string> name = getParametersFromCommand(command);

  if(name.size() > 1){
    throw CommandException("Invalid user of command /identify.");
  }

  Json::Value json;
  json["type"] = "IDENTIFY";
  json["username"] = name[0];

  return turnJsonToString(json);
  
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

std::string CommandManager::manageDisconnect(){
  Json::Value json;
  json["type"] = "DISCONNECT";

  return turnJsonToString(json);
}

std::vector<std::string> CommandManager::getParametersFromCommand(std::vector<std::string> command){

  std::vector<std::string> parameters;
  std::string tempString = "";

  //Se marca el inicio del parámetro a obtener del comando.
  bool startValue;
  //Se indica el final del parámetro en el comando.
  bool endValue;

  for(int i = 1; i<command.size(); i++){
    
    for(char c : command[i]){
      
      if(c == '\''){
	
	if(startValue){
	  endValue = true;
	  parameters.push_back(tempString);
	  startValue = false;
	}else{
	  startValue = true;
	  endValue = false;
	  tempString = "";
	}
	
      }else if(startValue){
	
	tempString += c;
      }
    }

    tempString += " ";
  }

  if(!endValue || startValue){
    throw CommandException("Error: Incorrect use of delimiters. Make sure to use single quotes (') to delimit the command parameters.");
  }

  return parameters;
}

