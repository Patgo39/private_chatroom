#include "request_manager.h"

RequestManager::RequestManager(){
  jsonController = JsonController();
}

/**
 * Analiza el Json enviado por el cliente. Si no hay ningún error de formato
 * se procesa la petición, en caso contrario, se envía un mensaje de error.
 * @param requester referencia al objeto cliente que emitió la petición.
 * @param request la cadena con el json de la petición.
 * @param socketsMap referencia al mapa de clientes
 * @param roomMap referencia al mapa de cuertos privados.
 * @return objeto respuesta con los detalles de la petición.
 */
RequestResponse RequestManager::getResponse(Client &requester, std::string request, std::map<int, Client> &socketsMap, std::map<std::string, Room> &roomMap){
  RequestResponse response = RequestResponse();
  ServerData data(requester, socketsMap, roomMap);
  
  Json::CharReaderBuilder builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(request);
  bool ok = parseFromStream(builder, streamRequest, &value, &errs);

  if(!ok){
    /** Se manda error de que el servidor no recibe json y se desconecta*/
    return getInvalidRequestResponse(data);
  }

  if(!value.isMember("type")){
    /** Se manda error de json incompleto y se deconecta al usuario*/
    return getInvalidRequestResponse(data);
  }

  std::string type = value["type"].asString();
  
  if(type != "IDENTIFY" && !requester.isIdentified()){
    /** Se manda error de usuario no identificado y se desconecta*/
    response.stopConection();
    response.setUserResponse(jsonController.getNotIdentifiedResponse());
    return response;
  }
  
  if(type == "IDENTIFY"){
    return manageIdentifyRequest(value, data);
  }

  if(type == "STATUS"){
    return manageStatusRequest(value, data);
  }

  if(type == "TEXT"){
    return manageTextRequest(value, data);
  }

  if(type == "PUBLIC_TEXT"){
    return managePublicTextRequest(value, data);
  }

  if(type == "NEW_ROOM"){
    return manageNewRoomRequest(value, data);
  }

  return getInvalidRequestResponse(data);
}

/**
 * Administra la petición de identificación. Si todo el formato del json
 * recibido es correcto y los requisitos de registro son correctos, se agrega
 * un nuevo objeto cliente a la referencia al mapa de clientes del servidor.
 * Se crea el Json de respuesta al emisor y el Json de aviso a los demás
 * clientes.
 * @param value el valor del objeto Json.
 * @param requester la referencia al emisor.
 * @param socketsMap la referencia al mapa de clientes del servidor.
 * @return response el objeto respuesta con el mensaje al emisor y demás
 * clientes.
 */
RequestResponse RequestManager::manageIdentifyRequest(Json::Value value, ServerData data){

  // Si no se encuentra la llave username en el json se manda al usuario un mensaje de error.
  if(!value.isMember("username")){
    return getInvalidRequestResponse(data);
  }
  
  std::string username = value["username"].asString();
  username = trim(username);
  RequestResponse response = RequestResponse();

  if(username.length() > 8){
    response.setUserResponse(jsonController.getUsernameMaxCharResponse(username));
    response.stopConection();
    return response;
  }

  // Si existe el nombre de usuario no se ejecuta la petición.
  for(const auto& pair : data.socketsMap){
    Client c = pair.second;
    if(c.getUserName() == username){
      response.setUserResponse(jsonController.getUsernameAlreadyExistsResponse(username));
      return response;
    }
  }
  
  // Se modifica al cliente de acuerdo a la petición.
  data.requester.setUserName(username);
  data.requester.identify();

  // Se crea la respuesta json para el emisor.
  response.setUserResponse(jsonController.getIdentificationResponse(username));
  // Se crea la respuesta json para los demás clientes.
  response.setGeneralMessage(jsonController.getNewUserAdvice(username));
  return response;
}

/**
 * Adminsitra la petición de cambio de estado. Si el formato del Json es
 * correcto se cambia el estado de la referencia del emisor y se crea el aviso
 * de cambio de estado a los demás clientes conectados.
 * @param value el valor del Json recibido.
 * @param requester la referencia al objeto Cliente del emisor.
 * @return response el objeto respuesta con los detalles de la petición.
 */
RequestResponse RequestManager::manageStatusRequest(Json::Value value, ServerData data){

  if(!value.isMember("status")){
    return getInvalidRequestResponse(data);
  }
  
  std::string status = value["status"].asString();
  RequestResponse response = RequestResponse();

  UserStatus::Status statusValue= UserStatus::getStatusFromString(status);
  data.requester.setUserStatus(statusValue);
  status = data.requester.getUserStatus();

  std::string message = jsonController.getNewStatusAdvice(data.requester);
  response.setGeneralMessage(message);
  response.setUserResponse(message);
  return response;
}

/**
 * Administra la petición de la lista de usuarios general. Si el formato del
 * Json es correcto se crea el mensaje para el usuario con la lista de usuarios.
 * @param value el valor del Json recibido.
 * @param socketsMap el mapa de clientes conectados.
 * @return response la respuesta a la petición del usuario.
 */
RequestResponse RequestManager::manageUsersRequest(Json::Value value, ServerData data){

  RequestResponse response = RequestResponse();

  response.setUserResponse(jsonController.getServerUserListResponse(data.socketsMap));
  return response;
}

/**
 * Administrala petición del usuario para mandar un mensaje privado.
 * Si el formato del
 * Json es correcto se crea el mensaje para el usuario objetivo.
 * @param value el valor del Json recibido.
 * @param socketsMap el mapa de clientes conectados.
 * @param requester el objeto Cliente del emisor.
 * @return response la respuesta a la petición del usuario.
 */
RequestResponse RequestManager::manageTextRequest(Json::Value value, ServerData data){

  // Si no se encuentra la etiqueta username o text en el json se desconecta al usuario.
  if(!value.isMember("username") || !value.isMember("text")){
    return getInvalidRequestResponse(data);
  }


  // Se obtiene el username y el texto privado del json.
  RequestResponse response = RequestResponse();
  std::string userTarget = value["username"].asString();
  std::string text = value["text"].asString();
  bool userExists;
  int socketTarget;

  // Mensaje vacío
  if(text == ""){
    return response;
  }

  // Revisa que el usuario a quén se va a enviar el mensaje privado existe
  for(const auto& pair : data.socketsMap){
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
  
  std::string privateText = jsonController.getPrivateTextAdvice(data.requester.getUserName(), text);
  response.setSpecificMessage(privateText, {socketTarget});
  return response;
}

RequestResponse RequestManager::managePublicTextRequest(Json::Value value, ServerData data){

  if(!value.isMember("text")){
    return getInvalidRequestResponse(data);
  }
  
  RequestResponse response = RequestResponse();
  std::string text = value["text"].asString();
  std::string senderUsername = data.requester.getUserName();

  std::string json = jsonController.getPublicTextAdvice(senderUsername, text);
  response.setGeneralMessage(json);
  return response;
}

RequestResponse RequestManager::manageNewRoomRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();
  if(!value.isMember("roomname")){
    return getInvalidRequestResponse(data);
  }
  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);
  Room room = Room(roomName);
}


RequestResponse RequestManager::getInvalidRequestResponse(ServerData data){
  RequestResponse response = RequestResponse();
  response.stopConection();
  response.setUserResponse(jsonController.getInvalidJsonResponse());
  eraseClientData(data);
  return response;
}

void RequestManager::eraseClientData(ServerData data){
  // Socket del solicitante.
  int socket = data.requester.getSocket();
  // Lista de cuartos en los que se encuentra el cliente.
  std::vector<std::string> roomVector = data.requester.getRoomVector();
  // Se elimina el cliente de cada cuarto.
  for(std::string roomName : roomVector){
    Room tempRoom = data.roomMap.at(roomName);
    tempRoom.eraseUser(data.requester.getSocket());
  }
  
}

std::string RequestManager::trim(const std::string& str){
  size_t first = str.find_first_not_of(" \t\n\r\f\v"); // Find first non-whitespace character
  if (std::string::npos == first) { // If no non-whitespace characters found (string is all whitespace)
    return ""; // Return an empty string
  }
  size_t last = str.find_last_not_of(" \t\n\r\f\v"); // Find last non-whitespace character
  return str.substr(first, (last - first + 1));
}
