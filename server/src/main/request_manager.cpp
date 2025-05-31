#include "request_manager.h"

RequestManager::RequestManager(){
  jsonController = JsonController();
}

RequestResponse RequestManager::getResponse(Client &requester, std::string request, std::map<int, Client> &socketsMap, std::map<std::string, Room> &roomMap){
  RequestResponse data = RequestResponse();
  
  Json::CharReaderBuilder builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(request);
  bool ok = parseFromStream(builder, streamRequest, &value, &errs);

  if(!ok){
    /** Se manda error de que el servidor no recibe json y se desconecta*/
    return getInvalidRequestResponse();
  }

  if(!value.isMember("type")){
    /** Se manda error de json incompleto y se deconecta al usuario*/
    return getInvalidRequestResponse();
  }

  std::string type = value["type"].asString();
  
  if(type != "IDENTIFY" && !requester.isIdentified()){
    /** Se manda error de usuario no identificado y se desconecta*/
    data.stopConection();
    data.setUserResponse(jsonController.getNotIdentifiedResponse());
    return data;
  }
  
  if(type == "IDENTIFY"){
    return manageIdentifyRequest(value, requester, socketsMap);
  }

  if(type == "STATUS"){
    return manageStatusRequest(value, requester);
  }

  if(type == "TEXT"){
    return manageTextRequest(value, socketsMap, requester);
  }

  if(type == "PUBLIC_TEXT"){
    return managePublicTextRequest(value, requester);
  }

  return getInvalidRequestResponse();
}

RequestResponse RequestManager::manageIdentifyRequest(Json::Value value, Client &requester, std::map<int, Client> &socketsMap){

  if(!value.isMember("username")){
    return getInvalidRequestResponse();
  }
  
  std::string username = value["username"].asString();
  RequestResponse response = RequestResponse();

  if(username.length() > 8){
    response.setUserResponse(jsonController.getUsernameMaxCharResponse(username));
    return response;
  }

  for(const auto& pair : socketsMap){
    Client c = pair.second;
    if(c.getUserName() == username){
      response.setUserResponse(jsonController.getUsernameAlreadyExistsResponse(username));
      return response;
    }
  }
  
  // Se modifica al cliente de acuerdo a la petición.
  requester.setUserName(username);
  requester.identify();

  // Se crea la respuesta para el servidor.
  response.setUserResponse(jsonController.getIdentificationResponse(username));
  response.setGeneralMessage(jsonController.getNewUserAdvice(username));
  return response;
}

RequestResponse RequestManager::manageStatusRequest(Json::Value value, Client &requester){

  if(!value.isMember("status")){
    return getInvalidRequestResponse();
  }
  
  std::string status = value["status"].asString();
  RequestResponse response = RequestResponse();

  UserStatus::Status statusValue= UserStatus::getStatusFromString(status);
  requester.setUserStatus(statusValue);
  status = requester.getUserStatus();

  std::string message = jsonController.getNewStatusAdvice(requester);
  response.setGeneralMessage(message);
  response.setUserResponse(message);
  return response;
}

RequestResponse RequestManager::manageUsersRequest(Json::Value value, std::map<int, Client> socketsMap){

  RequestResponse response = RequestResponse();

  response.setUserResponse(jsonController.getServerUserListResponse(socketsMap));
  return response;
}

RequestResponse RequestManager::manageTextRequest(Json::Value value, std::map<int, Client> socketsMap, Client requester){

  if(!value.isMember("username") || !value.isMember("text")){
    return getInvalidRequestResponse();
  }
  
  RequestResponse response = RequestResponse();
  std::string userTarget = value["username"].asString();
  std::string text = value["text"].asString();
  bool userExists;
  int socketTarget;
  
  if(text == ""){
    return response;
  }

  for(const auto& pair : socketsMap){
    Client c = pair.second;
    if(c.getUserName() == userTarget){
      userExists = true;
      socketTarget = c.getSocket();
    }
  }

  if(!userExists){
    response.setUserResponse(jsonController.getNoSuchUserResponse(userTarget, Operation::Type::TEXT));
    return response;
  }
  
  std::string privateText = jsonController.getPrivateTextAdvice(requester.getUserName(), text);
  response.setSpecificMessage(privateText, {socketTarget});
  return response;
}

RequestResponse RequestManager::managePublicTextRequest(Json::Value value, Client requester){

  if(!value.isMember("text")){
    return getInvalidRequestResponse();
  }
  
  RequestResponse response = RequestResponse();
  std::string text = value["text"].asString();
  std::string senderUsername = requester.getUserName();

  std::string json = jsonController.getPublicTextAdvice(senderUsername, text);
  response.setGeneralMessage(json);
  return response;
}

RequestResponse RequestManager::getInvalidRequestResponse(){
  RequestResponse data = RequestResponse();
  data.stopConection();
  data.setUserResponse(jsonController.getInvalidJsonResponse());
  return data;
}
