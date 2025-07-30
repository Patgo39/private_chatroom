#include "server_response_manager.h"

ServerResponseManager::ServerResponseManager(){
  jsonError = "ERROR: Invalid server JSON format.";
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
    throw ServerResponseException("ERROR: Server response is not a JSON.");
  }

  if(!value.isMember("type")){
    throw ServerResponseException("Server response has no 'type' key.");
  }

  std::string type = value["type"].asString();
  
  if(type == "RESPONSE"){
    return manageServerResponse(value);
  }
  return manageServerAdvice(value);
}

Message ServerResponseManager::manageServerResponse(Json::Value value){
  if(!value.isMember("operation") || !value.isMember("result")){
    throw ServerResponseException(jsonError);
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

  // Se obtiene un objeto de la enumeración Operation a partir del json recibido.
  Operation op;
  try{
    op = OperationEnum::getOperationFromString(operation);    
  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError);
  }
  // Se obtiene el valor de la llave extra.
  if(!value.isMember("extra")){
    throw ServerResponseException(jsonError);
  }
  std::string extra = value["extra"].asString();

  // Caso en el que la operación fue exitosa.
  if(result == "SUCCESS"){
    
    switch (op) {
    case Operation::IDENTIFY:
      text = "\nYou have successfully identified yourself";
      break;
    case Operation::NEW_ROOM:
      text = "\nThe room named " + extra + " has been successfully created.";
      message.setRoomCreationWithAdvice(extra, text);
      return message;
    case Operation::JOIN_ROOM:
      text = "\nYou have successfully joined the room " + extra;
      message.setRoomCreationWithAdvice(extra, text);
      return message;
    default:
      throw ServerResponseException(jsonError);
    }
    
    message.setServerResponse(text, true);
    return message;
  }

  // Caso en que la operación no fue exitosa.
  try{
    Result rs = ResultEnum::getResultFromString(result);
    switch(rs){
    case Result::USER_ALREADY_EXISTS:
      text = "\nOperation failed: the username "+extra+" already exists.";
      message.setServerResponse(text, false);
      return message;
    case Result::NO_SUCH_USER:
      text = "\nOperation failed: " + extra + " does not exist";
      break;
    case Result::ROOM_ALREADY_EXISTS:
      text = "\nOperation failed: The room " + extra + "already exists";
      break;
    case Result::NO_SUCH_ROOM:
      text = "\nOperation failed: The room " + extra + "does not exist";
      break;
    case Result::NOT_INVITED:
      text = "\nOperation failed: You have not yet invited to the room " + extra;
      break;
    case Result::NOT_JOINED:
      text = "\nOperation failed: You have not yet joined to the room " + extra;
      break;
    case Result::NAME_TOO_LONG:
      text = "\nOperation failed: The provided name " +extra + " is too long";
      break; 
    }

    message.setServerResponse(text, true);
    return message;
  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError);
  }

  // Si el formato del json no contiene operaciones Invalidas o resultados
  // exitosos, el formato del JSON recibido es erroneo.
  throw ServerResponseException(jsonError);
}

Message ServerResponseManager::manageServerAdvice(Json::Value value){
  try{

  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError);
  }
}

