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
  return "";
}

std::string JsonController::getUsernameAlreadyExistsResponse(std::string username){
  return "";
}

std::string JsonController::getServerUserListResponse(std::map<int, Client> usersMap){
  return "";
}

std::string JsonController::getUserTargetDoesntExistsResponse(std::string username){
  return "";
}

std::string JsonController::getNewRoomCreatedResponse(std::string roomName){
  return "";
}

std::string JsonController::getRoomAlreadyExistsResponse(std::string roomName){
  return "";
}
 
std::string JsonController::getNoSuchRoomResponse(std::string roomName, Operation::Type type){
  return "";
}

std::string JsonController::getNoSuchUserResponse(std::string username, Operation::Type type){
  return "";
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
  return "";
}

std::string JsonController::getNewStatusAdvice(Client client){
  return "";
}

std::string JsonController::getPrivateTextAdvice(std::string username, std::string message){
  return "";
}

std::string JsonController::getPublicTextAdvice(std::string username, std::string message){
  return "";
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
  return "";
}

std::string JsonController::getUserDisconnectedAdvice(std::string username){
  return "";
}

