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

  std::string type = value["type"].asString();

  if(type == ""){
    /** Se manda error de json incompleto y se deconecta al usuario*/
    return getInvalidRequestResponse();
  }
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

  return getInvalidRequestResponse();
}

RequestResponse RequestManager::manageIdentifyRequest(Json::Value value, Client &requester, std::map<int, Client> &socketsMap){
  std::string username = value["username"].asString();
  RequestResponse response = RequestResponse();

  if(username == ""){
    return getInvalidRequestResponse();
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
  std::string status = value["status"].asString();
  RequestResponse response = RequestResponse();

  UserStatus::Status statusValue= UserStatus::getStatusFromString(status);
  requester.setUserStatus(statusValue);
  status = requester.getUserStatus();

  response.setGeneralMessage(jsonController.getNewStatusAdvice(requester));
  return response;
}

RequestResponse RequestManager::getInvalidRequestResponse(){
  RequestResponse data = RequestResponse();
  data.stopConection();
  data.setUserResponse(jsonController.getInvalidJsonResponse());
  return data;
}
