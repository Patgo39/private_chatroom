#include "json_controller.h"

JsonController::JsonController(){
}

/**Errores de formato*/
std::string JsonController::getInvalidJsonResponse(){
  Json::Value json;
  json["type"] = "RESPONSE";
  json["operation"] = "INVALID";
  json["result"] = "INVALID";

  return turnJsonToString(json);
}

std::string JsonController::getNotIdentifiedResponse(){
  Json::Value json;
  json["type"] = "RESPONSE";
  json["operation"] = "INVALID";
  json["result"] = "NOT_IDENTIFIED";

  return turnJsonToString(json);
}

std::string JsonController::turnJsonToString(Json::Value json){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, json);
  return output;
}

/**Respuestas para el solicitante de la petición*/
std::string JsonController::getIdentificationResponse(std::string username){
  Json::Value json;

  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "SUCCESS";
  json["extra"] = username;
  
  return turnJsonToString(json);
}

std::string JsonController::getUsernameAlreadyExistsResponse(std::string username){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "USER_ALREADY_EXISTS";
  json["extra"] = username;

  return turnJsonToString(json);
}

std::string JsonController::getUsernameMaxCharResponse(std::string username){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "USERNAME_TOO_LONG";
  json["extra"] = username;

  return turnJsonToString(json);
}

std::string JsonController::getServerUserListResponse(std::map<int, Client> usersMap){
  Json::Value json;
  Json::Value users;

  for(const auto& pair : usersMap){
    Client c = pair.second;

    users[c.getUserName()] = c.getUserStatus();
  }
  
  json["type"] = "USER_LIST";
  json["users"] = users;

  return turnJsonToString(json);
}

std::string JsonController::getNewRoomCreatedResponse(std::string roomName){
  return "";
}

std::string JsonController::getNewRoomMaxCharResponse(std::string roomName){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "ROOMNAME_TOO_LONG";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

std::string JsonController::getRoomAlreadyExistsResponse(std::string roomName){
  return "";
}
 
std::string JsonController::getNoSuchRoomResponse(std::string roomName, Operation::Type type){
  return "";
}

std::string JsonController::getNoSuchUserResponse(std::string username, Operation::Type type){

  std::string operation;
  
  switch(type){
  case Operation::Type::INVITE: operation = "INVITE"; break;
  case Operation::Type::TEXT: operation = "TEXT"; break;
  default: /**Lanza error*/break;
  }
  
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = operation;
  json["result"] = "NO_SUCH_USER";
  json["extra"] = username;

  return turnJsonToString(json);
}

std::string JsonController::getJoinRoomSuccessResponse(std::string roomName){
  return "";
}

std::string JsonController::getNotInvitedResponse(std::string roomName, Operation::Type type){
  return "";
}

std::string JsonController::getNotJoinedResponse(std::string roomName, Operation::Type type){
  return "";
}

std::string JsonController::getRoomUsersResponse(std::vector<Client> roomUsers){
  return "";
}


  /**Mensajes generales*/
std::string JsonController::getNewUserAdvice(std::string username){
  Json::Value json;

  json["type"] = "NEW_USER";
  json["username"] = username;

  return turnJsonToString(json);

}

std::string JsonController::getNewStatusAdvice(Client client){
  Json::Value json;

  json["type"] = "NEW_STATUS";
  json["username"] = client.getUserName();
  json["status"] = client.getUserStatus();

  return turnJsonToString(json);
}

std::string JsonController::getPrivateTextAdvice(std::string username, std::string message){
  Json::Value json;

  json["type"] = "TEXT_FROM";
  json["username"] = username;
  json["text"] = message;

  return turnJsonToString(json);
}

std::string JsonController::getPublicTextAdvice(std::string username, std::string message){
  
  Json::Value json;

  json["type"] = "PUBLIC_TEXT";
  json["text"] = message;

  return turnJsonToString(json);
}

std::string JsonController::getInvitationAdvice(std::string username, std::string roomName){
  return "";
}

std::string JsonController::getUserJoinedRoomAdvice(std::string username, std::string roomName){
  return "";
}

std::string JsonController::getRoomTextAdvice(std::string username, std::string roomName, std::string message){
  return "";
}

std::string JsonController::getLeftRoomAdvice(std::string username, std::string roomName){

  Json::Value json;

  json["type"] = "LEFT_ROOM";
  json["roomname"] = roomName;
  json["username"] = username;

  return turnJsonToString(json);
}

std::string JsonController::getUserDisconnectedAdvice(std::string username){

  Json::Value json;

  json["type"] = "DISCONNECTED";
  json["username"] = username;

  return turnJsonToString(json);
}

