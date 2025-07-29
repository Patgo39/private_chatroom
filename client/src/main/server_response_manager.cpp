#include "server_response_manager.h"

ServerResponseManager::ServerResponseManager(){
}

Message ServerResponseManager::getMessageFromResponse(std::string serverResponse){
  message = Message();
  
  Json::CharReaderBuilder builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(serverResponse);
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
  if(!value.isMember("operation") || !value.isMember("result")){
    throw ServerResponseException("Invalid server JSON format.");
  }

  std::string operation = value["operation"].asString();
  std::string result = value["result"].asString();
  std::string text;
  
    if(operation == "INVALID"){
      if(result == "NOT_IDENTIFIED"){
	text = 
     "\nERROR: Unauthorized action detected. You must log in before performing "
      "any operations.\nThe connection will now be terminated.";

	message.setServerResponse(text, false);
	return message;
      }

      text = "ERROR: Invalid operation format detected.\n"
  "The request sent by the client does not comply with the required protocol.\n"
	"The connection will be terminated.";
      message.setServerResponse(text, false);
      return message;
    }

    if(result == "SUCCESS"){
      
    }
  
}

Message ServerResponseManager::manageServerAdvice(Json::Value value){
  
}

