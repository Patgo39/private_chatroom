#include "server_response_manager.h"

ServerResponseManager::ServerResponseManager(){}

Message ServerResponseManager::getMessageFromResponse(std::string serverResponse){
  Json::CharReaderBuider builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(request);
  bool ok = parseFromStream(builder, streamRequest, &value, &errs);

  if(!ok){
    throw ServerResponseException("Server response is not a JSON.");
  }

  if(!value.isMember("type")){
    throw ServerResponseException("Server response has no 'type' key.");
  }

  std::string type = value["type"].asString();
  
  if(type == "RESPONSE"){
    manageServerResponse(value);
  }else{
    manageServerAdvice(value);
  }
}

Message ServerResponseManager::manageServerResponse(Json::Value value){
  
}

Message ServerResponseManager::manageServerAdvice(Json::Value value){
  
}

