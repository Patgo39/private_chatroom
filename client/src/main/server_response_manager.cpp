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
    throw ServerResponseException(jsonError.c_str());
  }

  std::string operation = value["operation"].asString();
  std::string result = value["result"].asString();
  std::string text;
  
  if(operation == "INVALID"){
    if(result == "NOT_IDENTIFIED"){
      text = 
	"ERROR: Unauthorized action detected. You must log in before performing "
	"any operations.\nThe connection will be terminated in 10 seconds.";
      
      message.setServerResponse(text, false);
      return message;
    }
    
    text = "ERROR: Invalid operation format detected.\n"
      "The request sent by the client does not comply with the required protocol.\n"
      "The connection will be terminated in 10 seconds.";
    message.setServerResponse(text, false);
    return message;
  }

  // Se obtiene un objeto de la enumeración Operation a partir del json recibido.
  Operation op;
  try{
    op = OperationEnum::getOperationFromString(operation);    
  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError.c_str());
  }
  // Se obtiene el valor de la llave extra.
  if(!value.isMember("extra")){
    throw ServerResponseException(jsonError.c_str());
  }
  std::string extra = value["extra"].asString();

  // Caso en el que la operación fue exitosa.
  if(result == "SUCCESS"){
    
    switch (op) {
    case Operation::IDENTIFY:
      text = "You have successfully identified yourself.";
      break;
    case Operation::NEW_ROOM:
      text = "The room named " + extra + " has been successfully created.";
      message.setRoomCreationWithAdvice(extra, text);
      return message;
    case Operation::JOIN_ROOM:
      text = "You have successfully joined the room " + extra + ".";
      message.setRoomCreationWithAdvice(extra, text);
      return message;
    default:
      throw ServerResponseException(jsonError.c_str());
    }
    
    message.setServerResponse(text, true);
    return message;
  }

  // Caso en que la operación no fue exitosa.
  try{
    Result rs = ResultEnum::getResultFromString(result);
    switch(rs){
    case Result::USER_ALREADY_EXISTS:
      text = "Operation failed: the username "+extra+" already exists.";
      text += "\nThe connection will be terminated in 10 seconds.";
      message.setServerResponse(text, false);
      return message;
    case Result::NO_SUCH_USER:
      text = "Operation failed: " + extra + " does not exist.";
      break;
    case Result::ROOM_ALREADY_EXISTS:
      text = "Operation failed: The room " + extra + " already exists.";
      break;
    case Result::NO_SUCH_ROOM:
      text = "Operation failed: The room " + extra + " does not exist.";
      break;
    case Result::NOT_INVITED:
      text = "Operation failed: You have not yet invited to the room " + extra + ".";
      break;
    case Result::NOT_JOINED:
      text = "Operation failed: You have not yet joined to the room " + extra + ".";
      break;
    case Result::NAME_TOO_LONG:
      text = "Operation failed: The provided name " +extra + " is too long.";
      break; 
    }

    message.setServerResponse(text, true);
    return message;
  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError.c_str());
  }

  // Si el formato del json no contiene operaciones Invalidas o resultados
  // exitosos, el formato del JSON recibido es erroneo.
  throw ServerResponseException(jsonError.c_str());
}

Message ServerResponseManager::manageServerAdvice(Json::Value value){
  std::string text = "";
  try{
    UserAdvice userad = UserAdviceEnum::getUserAdviceFromString(value["type"].asString());
    switch (userad) {
    case UserAdvice::NEW_USER:
      {
	if(!value.isMember("username")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	text = "'" + userName + "' has joined the chat.";
	break;
      }
    case UserAdvice::NEW_STATUS:
      {
	if(!value.isMember("username") || !value.isMember("status")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string status = value["status"].asString();
	text = userName + " has changed their status to " + status + ".";
	break;
      }
      
    case UserAdvice::USER_LIST:
      {
	if(!value.isMember("users")){
	  throw ServerResponseException(jsonError.c_str());
	}
	Json::Value users_json = value["users"];
	if(!users_json.isObject()){
	  throw ServerResponseException(jsonError.c_str());
	}
	
	text = "Users List:\n";
	for(Json::ValueConstIterator itr = users_json.begin(); itr != users_json.end(); ++itr){
	  text += "\tName: " + itr.name() + " | Status: " + itr->asString() + ", \n";
	}
	message.setServerResponse(text, true);
	return message;
	break;
      }
    case UserAdvice::TEXT_FROM:
      {
	if(!value.isMember("username") || !value.isMember("text")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string msg = value["text"].asString();
	message.setPrivateMessage(msg, userName);
	return message;
	break;
      }
      
    case UserAdvice::PUBLIC_TEXT_FROM:
      {
	if(!value.isMember("username") || !value.isMember("text")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string msg = value["text"].asString();
	message.setPublicMessage(msg, userName);
	return message;
	break;
      }
    case UserAdvice::INVITATION:
      {
	if(!value.isMember("username") || !value.isMember("roomname")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string roomName = value["roomname"].asString();
	text = userName + " invited you to room '" + roomName + "'.";
	break;
      }
    case UserAdvice::JOINED_ROOM:
      {
	if(!value.isMember("username") || !value.isMember("roomname")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string roomName = value["roomname"].asString();
	text = userName + " has joined to the room.";
	message.setRoomAdvice(text, roomName);
	return message;
      }
      
    case UserAdvice::ROOM_USER_LIST:
      {
	if(!value.isMember("users") || !value.isMember("roomname")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string roomName = value["roomname"].asString();
	Json::Value users_json = value["users"];
	if(!users_json.isObject()){
	  throw ServerResponseException(jsonError.c_str());
	}
	
	text = "Room Users:\n";
	for(Json::ValueConstIterator itr = users_json.begin(); itr != users_json.end(); ++itr){
	  text += "\tName: " + itr.name() + " | Status: " + itr->asString() + ", \n";
	}
	message.setRoomAdvice(text, roomName);
	return message;
      }
    case UserAdvice::ROOM_TEXT_FROM:
      {
	if(!value.isMember("username") || !value.isMember("roomname") || !value.isMember("text")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string roomName = value["roomname"].asString();
	std::string msg = value["text"].asString();
	message.setRoomMessage(msg, roomName, userName);
	return message;
      }
      
    case UserAdvice::LEFT_ROOM:
      {
	if(!value.isMember("username") || !value.isMember("roomname")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	std::string roomName = value["roomname"].asString();
	text = userName + " has left the room.";
	message.setRoomAdvice(text, roomName);
	return message;
	break;
      }
      
    case UserAdvice::DISCONNECTED:
      {
	if(!value.isMember("username")){
	  throw ServerResponseException(jsonError.c_str());
	}
	std::string userName = value["username"].asString();
	text = userName + " has disconnected from the chat.";
	break;
      }
    }

    message.setServerAdvice(text);
    return message;
  }catch(const std::invalid_argument& e){
    throw ServerResponseException(jsonError.c_str());
  }
}

