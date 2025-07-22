#include "command_manager.h"

CommandManager::CommandManager(){

}

/**
 * Analiza el caso de todo comando posible incluyendo los posibles errores y
 * se trabaja con el comando según sea el caso.
 * @param userMessage el mensaje del usuario con el comando.
 * @param stillConnected referencia a un booleano <True> para que el cliente
 * mantenga la conexión con el servidor y <False> para otro caso.
 * @return Json del comando recibido.
 **/
std::string CommandManager::getJsonFromCommand(std::string userMessage, bool &stillConnected){
  std::vector<std::string> command = getCommandAsVector(userMessage);

  if(command[0] == "/identify"){
    return manageIdentification(command);
    
  }else if(command[0] == "/changestatus"){
    return manageNewStatus(command);
    
  }else if(command[0] == "/list"){
    return manageUsersList(command);
    
  }else if(command[0] == "/private"){
     return managePrivateMessage(command);
    
  }else if(command[0] == "/newroom"){
    return manageNewRoom(command);
    
  }else if(command[0] == "/invite"){
    return manageInviteUsersToRoom(command);
    
  }else if(command[0] == "/join"){
    return manageJoinRoom(command);
    
  }else if(command[0] == "/roomlist"){
    return manageRoomList(command);
    
  }else if(command[0] == "/leave"){
    return manageLeaveRoom(command);
    
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

/**
 * Convierte el comando del usuario en un vector.
 * @param userMessage el mensaje del usuario con el comando.
 * @return command el comando del usuario convertido a vector.
 **/
std::vector<std::string> CommandManager::getCommandAsVector(std::string userMessage){
  std::vector<std::string> command;
  std::string temp;
  std::stringstream ss(userMessage);

  while(getline(ss, temp, ' ')){
    command.push_back(temp);
  }
  return command;
}

/**
 * Construye el Json del comando para el comando de un mensaje público.
 * @param userMessage el mensaje del usuario con el comando.
 * @return el String con el json del comando.
 **/
std::string CommandManager::manageNormalText(std::string userMessage){
  Json::Value json;
  json["type"] = "PUBLIC_TEXT";
  json["text"] = userMessage;

  return turnJsonToString(json);
}

/**
 * Convierte un objeto Json a un String.
 * @param json el objeto json.
 * @return output el String con el Json 
 **/
std::string CommandManager::turnJsonToString(Json::Value json){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, json);
  return output;
}

/**
 * Convierte el comando /identify a Json y luego a String.
 * @param command el vector con el comando del usuario.
 * @return el String del json del comando.
 **/
std::string CommandManager::manageIdentification(std::vector<std::string> command){

  std::vector<std::string> name = getParametersFromCommand(command);

  if(name.size() > 1 || name.size() < 1){
    throw CommandException("Invalid use of command /identify.");
  }

  Json::Value json;
  json["type"] = "IDENTIFY";
  json["username"] = name[0];

  return turnJsonToString(json);
  
}

std::string CommandManager::manageNewStatus(std::vector<std::string> command){
  
  std::vector<std::string> newStatus = getParametersFromCommand(command);

  if(newStatus.size() > 1 || newStatus.size() < 1){
    throw CommandException("Invalid use of command /status.");
  }

  for(char l:newStatus[0]){
    l = toupper(l);
  }
  
  Json::Value json;
  json["type"] = "STATUS";
  json["status"] = newStatus[0];

  return turnJsonToString(json);

}

std::string CommandManager::manageUsersList(std::vector<std::string> command){
  
  Json::Value json;
  json["type"] = "USERS";

  return turnJsonToString(json);
}

std::string CommandManager::managePrivateMessage(std::vector<std::string> command){
  std::vector<std::string> parameters = getParametersFromCommand(command);

  if(parameters.size() > 2 || parameters.size() < 2){
    throw CommandException("Invalid use of command /private.");
  }
  
  Json::Value json;
  json["type"] = "TEXT";
  json["username"] = parameters[0];
  json["text"] = parameters[1];

  return turnJsonToString(json);
}

std::string CommandManager::manageNewRoom(std::vector<std::string> command){
  std::vector<std::string> roomname = getParametersFromCommand(command);

  if(roomname.size() > 1 || roomname.size() < 1){
    throw CommandException("Invalid use of command /newroom.");
  }

  Json::Value json;
  json["type"] = "NEW_ROOM";
  json["roomname"] = roomname[0];

  return turnJsonToString(json);
}

std::string CommandManager::manageInviteUsersToRoom(std::vector<std::string> command){
  std::vector<std::string> parameters = getParametersFromCommand(command);

  if(parameters.size() < 2){
    throw CommandException("Invalid use of command /invite.");
  }
  
  Json::Value jsonArray;

  for(std::size_t i = 1; i< parameters.size(); i++){
    jsonArray.append(parameters[i]);
  }
  
  Json::Value json;
  json["type"] = "INVITE";
  json["roomname"] = parameters[0];
  json["usernames"] = jsonArray;

  return turnJsonToString(json);
}

std::string CommandManager::manageJoinRoom(std::vector<std::string> command){

  std::vector<std::string> roomname = getParametersFromCommand(command);
  
  if(roomname.size() > 1 || roomname.size() < 1){
    throw CommandException("Invalid use of command /join.");
  }

  Json::Value json;
  json["type"] = "JOIN_ROOM";
  json["roomname"] = roomname[0];

  return turnJsonToString(json);
}

std::string CommandManager::manageRoomList(std::vector<std::string> command){

  std::vector<std::string> roomname = getParametersFromCommand(command);
  
  if(roomname.size() > 1 || roomname.size() < 1){
    throw CommandException("Invalid use of command /roomlist.");
  }

  Json::Value json;
  json["type"] = "ROOM_USERS";
  json["roomname"] = roomname[0];

  return turnJsonToString(json);
}

std::string CommandManager::manageLeaveRoom(std::vector<std::string> command){

  std::vector<std::string> roomname = getParametersFromCommand(command);
  
  if(roomname.size() > 1 || roomname.size() < 1){
    throw CommandException("Invalid use of command /leave.");
  }

  Json::Value json;
  json["type"] = "LEAVE_ROOM";
  json["roomname"] = roomname[0];

  return turnJsonToString(json);
}

std::string CommandManager::manageDisconnect(){
  Json::Value json;
  json["type"] = "DISCONNECT";

  return turnJsonToString(json);
}

/**
 * Regresa los parámetros que se encuentran acotados por (').
 * @return vector un vector con todos los parámetros en el comando.
 */
std::vector<std::string> CommandManager::getParametersFromCommand(std::vector<std::string> command){

  std::vector<std::string> parameters;
  std::string tempString = "";

  //Se marca el inicio del parámetro a obtener del comando.
  bool startValue;
  //Se indica el final del parámetro en el comando.
  bool endValue;

  //Recorre el commando
  for(std::string parameter : command){
    //Recorre cada carácter de una palabra en el comando.
    for(char c : parameter){

      /*Si se encuentra (') se marca como inicio del parámetro.
        Si ya se había marcado como inicio, se marca como final y se agrega al
        vector*/
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
	//Cualquier otro caracter es una letra del parámetro.
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

