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

  if(type == "USERS"){
    return manageUsersRequest(data);
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

  if(type == "INVITE"){
    return manageInviteRequest(value, data);
  }

  if(type == "JOIN_ROOM"){
    return manageJoinRoomRequest(value, data);
  }
  
  if(type == "ROOM_USERS"){
    return manageRoomUsersRequest(value, data);
  }
  
  if(type == "ROOM_TEXT"){
    return manageRoomTextRequest(value, data);
  }
  
  if(type == "LEAVE_ROOM"){
    return manageLeaveRoomRequest(value, data);
  }
  
  if(type == "DISCONNECT"){
    return manageDisconnectRequest(data);
  }
  return getInvalidRequestResponse(data);
}

/**
 * Administra la petición de identificación. Si el formato del json
 * recibido es correcto y los requisitos de registro son correctos, se agrega
 * un nuevo objeto cliente a la referencia del mapa de clientes del servidor.
 * Se crea el Json de respuesta al solicitante y el Json de aviso a los demás
 * clientes.
 * @param value el valor del objeto Json.
 * @param requester la referencia al solicitante.
 * @param socketsMap la referencia al mapa de clientes del servidor.
 * @return response el objeto respuesta con el mensaje al solicitante y demás
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

  if(data.requester.isIdentified()){
    return response;
  }
  
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

  // Se crea la respuesta json para el solicitante.
  response.setUserResponse(jsonController.getIdentificationResponse(username));
  // Se crea la respuesta json para los demás clientes.
  response.pushGeneralMessage(jsonController.getNewUserAdvice(username));
  return response;
}

/**
 * Adminsitra la petición de cambio de estado. Si el formato del Json es
 * correcto se cambia el estado del solicitante y se crea el aviso
 * de cambio de estado para los demás clientes conectados.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response el objeto respuesta con los detalles de la petición.
 */
RequestResponse RequestManager::manageStatusRequest(Json::Value value, ServerData data){

  // Si el formato del json es incorrecto, se le notifica al usuario y se desconecta.
  if(!value.isMember("status")){
    return getInvalidRequestResponse(data);
  }

  // Se obtiene el nuevo estado.
  std::string status = value["status"].asString();
  RequestResponse response = RequestResponse();

  // Se actualiza el cliente al nuevo estado.
  // Si el nuevo estado no existe, se actualiza el estado a ACTIVE
  UserStatus::Status statusValue= UserStatus::getStatusFromString(status);
  data.requester.setUserStatus(statusValue);
  status = data.requester.getUserStatus();

  // Se crea el Json y la respuesta.
  std::string message = jsonController.getNewStatusAdvice(data.requester);
  response.pushGeneralMessage(message);
  response.setUserResponse(message);
  return response;
}

/**
 * Administra la petición de la lista de usuarios general. Si el formato del
 * Json es correcto se crea el mensaje para el usuario con la lista de usuarios.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta a la petición del usuario.
 */
RequestResponse RequestManager::manageUsersRequest(ServerData data){

  // Se crea la respuesta con el Json de la lista de ususarios en el chat.
  RequestResponse response = RequestResponse();
  response.setUserResponse(jsonController.getServerUserListResponse(data.socketsMap));
  return response;
}

/**
 * Administrala petición del usuario para mandar un mensaje privado.
 * Si el formato del Json es correcto y existe el usuario, se crea la respuesta
 * para el destinatario. En caso contrario se le notifica al solicitante del error.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
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

  // Si el mensaje es vacío, no se realiza nada.
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

  // Si el usuario destinatario no existe, se le notifica al solicitante.
  if(!userExists){
    response.setUserResponse(jsonController.getNoSuchUserResponse(userTarget, Operation::Type::TEXT));
    return response;
  }

  // Se prepara la respuesta para el destinatario.
  std::string privateText = jsonController.getPrivateTextAdvice(data.requester.getUserName(), text);
  response.pushSpecificMessage(privateText, {socketTarget});
  return response;
}

/**
 * Crea la respuesta con el json que contiene el mensaje público.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el Json para los demás usuarios.
 */
RequestResponse RequestManager::managePublicTextRequest(Json::Value value, ServerData data){

  // Si el formato del Json recibido es incorrecto se le notifica al usuario.
  if(!value.isMember("text")){
    return getInvalidRequestResponse(data);
  }

  // Se obtiene el mensaje del Json.
  RequestResponse response = RequestResponse();
  std::string text = value["text"].asString();
  std::string senderUsername = data.requester.getUserName();

  // Se crea la respuesta.
  std::string json = jsonController.getPublicTextAdvice(senderUsername, text);
  response.pushGeneralMessage(json);
  return response;
}

/**
 * Crea el cuarto con el nombre especificado por el solicitante en el Json.
 * Si el formato del Json es correcto, se crea un objeto Room al cual se agrega
 * directamente el solicitante en su lista y se añade al mapa de cuartos del
 * servidor.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageNewRoomRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();
  // Si el formato del json es incorrecto se desconecta al solicitante.
  if(!value.isMember("roomname")){
    return getInvalidRequestResponse(data);
  }

  // Se eliminan espacios al inicio y al final del nombre del cuarto.
  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);

  // Si el nombre del cuarto es mayor a 16 caracteres, ocurre un error y se
  // notifica al solicitante.
  if(roomName.length() > 16){
    std::string json = jsonController.getNewRoomMaxCharResponse(roomName);
    response.setUserResponse(json);
    return response;
  }
  
  // Si el cuarto ya existe se le notifica al solicitante.
  if(data.roomMap.find(roomName) != data.roomMap.end()){
    std::string json = jsonController.getRoomAlreadyExistsResponse(roomName);
    response.setUserResponse(json);
    return response;
  }
  // Se crea el cuarto y se agrega al mapa de cuartos.
  int requesterSocket = data.requester.getSocket(); // Socket del cliente.
  Room room = Room(roomName);
  data.requester.joinToRoom(roomName); 
  room.inviteUser(requesterSocket);
  room.setUserToJoined(requesterSocket); // Se agrega al usuario a la lista del cuarto.
  data.roomMap.insert({roomName, room}); // Se agrega el cuarto al mapa de cuartos.

  // Se prepara la respuesta de petición exitosa.
  std::string json = jsonController.getNewRoomCreatedResponse(roomName);
  response.setUserResponse(json);
  return response;
}

/**
 * Se maneja la invitación de uno o más clientes a un cuarto. Si el formato del
 * Json es correcto, si existen todos los usuarios en el chat y el solicitante
 * ya se encuentra invitado y en el cuarto se crea el aviso para los
 * destinatarios.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageInviteRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();
  
  // Si el formato del Json es incompleto, se desconecta al solicitante.
  if(!value.isMember("roomname") || !value.isMember("usernames")){
    return getInvalidRequestResponse(data);
  }

  // Se obtiene el nombre del cuarto del Json recibido.
  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);
  // Se obtiene la lista de usuarios.
  Json::Value array = value["usernames"];
  if(!array.isArray()){
    return getInvalidRequestResponse(data);
  }
  
  std::vector<int> invitedSockets; 

  // Si no existe el cuarto se le notifica al usuario
  if(data.roomMap.find(roomName) == data.roomMap.end()){
    std::string json = jsonController.getNoSuchRoomResponse(roomName, Operation::Type::INVITE);
    response.setUserResponse(json);
    return response;
  }

  try{
    // Si el solicitante aún no se une, no se procesa la petición y se le notifica.
    if(!data.roomMap.at(roomName).isUserJoined(data.requester.getSocket())){
      std::string json = jsonController.getNotJoinedResponse(roomName, Operation::Type::INVITE);
      response.setUserResponse(json);
      return response;
    }

    // Se verifica que todos los clientes invitados estén en el mapa de sockets.
    for(Json::Value::ArrayIndex i = 0; i != array.size(); i++){
      std::string username = array[i].asString();
      bool finded = false;
      
      for(const auto& pair: data.socketsMap){
	Client c = pair.second;
	if(c.getUserName() == username){
	  finded = true;
	invitedSockets.push_back(c.getSocket());
	}
      }

      // Si no se encontró un cliente, no se procesa la solicitud y se le notifica al solicitante.
      if(!finded){
	std::string json = jsonController.getNoSuchUserResponse(username, Operation::Type::INVITE);
      response.setUserResponse(json);
      return response;
      }
    }
    
    // Se prepara el aviso para los usuarios invitados y se invitan al cuarto.
    std::string json = jsonController.getInvitationAdvice(data.requester.getUserName(), roomName);
    response.pushSpecificMessage(json, invitedSockets);
    
    // Se marcan los usuarios como invitados en el cuarto.
    for(int socket : invitedSockets){
      data.roomMap.at(roomName).inviteUser(socket);
    }
    
  }catch(NoSuchUserInRoomException &e){
    // Si el solicitante no está invitado, no se procesa la petición y se le notifica.
    std::string json = jsonController.getNotJoinedResponse(roomName, Operation::Type::INVITE);
    response.setUserResponse(json);
  }
  
  return response;
}

/**
 * Administra la petición de unirse a un cuarto. Si el formato del json es
 * correcto, el usuario fue previamente invitado y el cuarto existe, se crea la
 * respuesta.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageJoinRoomRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();

  // Si el formato del json no es correcto, se le notifica al solicitante.
  if(!value.isMember("roomname")){
    return getInvalidRequestResponse(data);
  }

  // Se obtiene el nombre del cuarto.
  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);

  // Se obtienen los datos del usuario.
  int requesterSocket = data.requester.getSocket();
  std::string username = data.requester.getUserName();

  // Si no existe el cuarto se le notifica al cliente.
  if(data.roomMap.find(roomName) == data.roomMap.end()){
    std::string json = jsonController.getNoSuchRoomResponse(roomName, Operation::Type::JOIN_ROOM);
    response.setUserResponse(json);
    return response;
  }

  try{
    // Si el usuario ya está invitado, no se realiza ningún aviso.
    if(data.roomMap.at(roomName).isUserJoined(requesterSocket)){
      return response;
    }
    // Se marca el usuario como unido y se le notifica a los demás en el cuarto.
    std::vector<int> joinedClients = data.roomMap.at(roomName).getJoinedClients();
    data.roomMap.at(roomName).setUserToJoined(requesterSocket);
    data.requester.joinToRoom(roomName);
    std::string json1 = jsonController.getJoinRoomSuccessResponse(roomName);
    response.setUserResponse(json1);
    std::string json2 = jsonController.getUserJoinedRoomAdvice(username, roomName);
    response.pushSpecificMessage(json2, joinedClients);
    
    
  }catch(NoSuchUserInRoomException &e){
    std::string json = jsonController.getNotInvitedResponse(roomName);
    response.setUserResponse(json);
    
  }
  
  return response;
}

/**
 * Administra la solicitud de la lista del cuarto. Si el formato del json es
 * correcto y el solicitante está en el cuarto se crea la respuesta.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageRoomUsersRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();

  // Si el formato del json es incorrecto se le notifica al solicitante.
  if(!value.isMember("roomname")){
    return getInvalidRequestResponse(data);
  }
  
  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);
  int requesterSocket = data.requester.getSocket();

  // Si no existe el cuarto se le notifica al cliente.
  if(data.roomMap.find(roomName) == data.roomMap.end()){
    std::string json = jsonController.getNoSuchRoomResponse(roomName, Operation::Type::ROOM_USERS);
    response.setUserResponse(json);
    return response;
  }

  try{
    // Si el usuario aún no se une se le notifica al solicitante.
    if(!data.roomMap.at(roomName).isUserJoined(requesterSocket)){
      std::string json = jsonController.getNotJoinedResponse(roomName, Operation::Type::ROOM_USERS);
      response.setUserResponse(json);
      return response;
    }
    
    // Se prepara la respuesta para el usuario.
    std::vector<int> joinedClients = data.roomMap.at(roomName).getJoinedClients();
    std::vector<Client> clientsInRoom;
    
    for(int cSocket : joinedClients){
      clientsInRoom.push_back(data.socketsMap.at(cSocket));
    }
    std::string json = jsonController.getRoomUsersResponse(roomName, clientsInRoom);
    response.setUserResponse(json);
    
  }catch(NoSuchUserInRoomException &e){
    // Si el usuario aún no está invitado, se le notifica al solicitante.
    std::string json = jsonController.getNotJoinedResponse(roomName, Operation::Type::ROOM_USERS);
    response.setUserResponse(json);
  }
  
  return response;
}

/**
 * Administra la petición de un mensaje a un cuarto. Si existe el cuarto y el
 * usuario está invitado se crea la respuesta a los demás clientes unidos al
 * cuarto.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageRoomTextRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();

  // Si el formato del json no es correcto, se le notifica al usuario.
  if(!value.isMember("roomname") || !value.isMember("text")){
    return getInvalidRequestResponse(data);
  }

  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);
  int requesterSocket = data.requester.getSocket();
  std::string userName = data.requester.getUserName();
  std::string text = value["text"].asString();
  std::string json;

  // Si no existe el cuarto se le notifica al cliente.
  if(data.roomMap.find(roomName) == data.roomMap.end()){
    json = jsonController.getNoSuchRoomResponse(roomName, Operation::Type::ROOM_TEXT);
    response.setUserResponse(json);
    return response;
  }

  try{
    // Si no se ha unido al cuarto se le notifica al cliente.
    if(!data.roomMap.at(roomName).isUserJoined(requesterSocket)){
      json = jsonController.getNotJoinedResponse(roomName, Operation::Type::ROOM_TEXT);
      response.setUserResponse(json);
      return response;
    }

    // Se prepara el aviso a los demás clientes en el cuarto.
    std::vector<int> joinedClients = data.roomMap.at(roomName).getJoinedClients();
    json = jsonController.getRoomTextAdvice(userName, roomName, text);
    response.pushSpecificMessage(json, joinedClients);
    
  }catch(NoSuchUserInRoomException &e){
    // Si no fue invitado al cuarto, se le notifica al cliente.
    json = jsonController.getNotJoinedResponse(roomName, Operation::Type::ROOM_TEXT);
    response.setUserResponse(json);
  }
  
  return response;
}

/**
 * Se administra la solicitud para abandonar el cuarto. Si el solicitante está
 * unido al cuarto y el cuarto existe, se le borra de la lista.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::manageLeaveRoomRequest(Json::Value value, ServerData data){
  RequestResponse response = RequestResponse();
  if(!value.isMember("roomname")){
    return getInvalidRequestResponse(data);
  }

  std::string roomName = value["roomname"].asString();
  roomName = trim(roomName);
  int requesterSocket = data.requester.getSocket();
  std::string userName = data.requester.getUserName();
  std::string json;

  // Si no existe el cuarto se le notifica al cliente.
  if(data.roomMap.find(roomName) == data.roomMap.end()){
    json = jsonController.getNoSuchRoomResponse(roomName, Operation::Type::LEAVE_ROOM);
    response.setUserResponse(json);
    return response;
  }

  try{
    // Si no se ha unido al cuarto se le notifica al cliente.
    if(!data.roomMap.at(roomName).isUserJoined(requesterSocket)){
      json = jsonController.getNotJoinedResponse(roomName, Operation::Type::LEAVE_ROOM);
      response.setUserResponse(json);
      return response;
    }
    // Se borra el usuario del cuarto y el cuarto del usuario.
    data.roomMap.at(roomName).eraseUser(data.requester.getSocket());
    data.requester.forgetRoom(roomName);
    std::vector<int> joinedClients = data.roomMap.at(roomName).getJoinedClients();
    json = jsonController.getLeftRoomAdvice(userName, roomName);
    response.pushSpecificMessage(json, joinedClients);

    if(joinedClients.size() <= 0){
      data.roomMap.erase(roomName);
    }
    
  }catch(NoSuchUserInRoomException &e){
    // Si no fue invitado al cuarto, se le notifica al cliente.
    json = jsonController.getNotJoinedResponse(roomName, Operation::Type::LEAVE_ROOM);
    response.setUserResponse(json);
  }
  
  return response;
}

/**
 * Administra la petición de desconectarse. Se borra la usuario del mapa de
 * sockets del servidor y se le notifica a los demás clientes.
 * @param value el valor del objeto Json.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante. 
 */
RequestResponse RequestManager::manageDisconnectRequest(ServerData data){
  RequestResponse response = RequestResponse();
  std::vector<std::string> roomVector = data.requester.getRoomVector();
  std::string userName = data.requester.getUserName();
  std::string json = "";
  
  // Se borra al solicitante de cada cuarto conectado y se le notifica a los
  // clientes unidos.
  for(std::string roomName : roomVector){
    data.roomMap.at(roomName).eraseUser(data.requester.getSocket());
    std::vector<int> clientsInRoom = data.roomMap.at(roomName).getJoinedClients();
    json = jsonController.getLeftRoomAdvice(userName, roomName);
    response.pushSpecificMessage(json, clientsInRoom);

    // Si el cuarto queda vacío, se elimina del mapa de cuartos.
    if(clientsInRoom.size() <= 0){
      data.roomMap.erase(roomName);
    }
  }
  json = jsonController.getUserDisconnectedAdvice(userName);
  response.pushGeneralMessage(json);
  response.stopConection();
  
  return response;
}

/**
 * Crea el aviso del formato de json incorrecto y se desconecta del chat.
 * @param data el struct con referencias a los datos del servidor.
 * @return response la respuesta con el aviso al solicitante.
 */
RequestResponse RequestManager::getInvalidRequestResponse(ServerData data){
  RequestResponse response = manageDisconnectRequest(data);
  response.setUserResponse(jsonController.getInvalidJsonResponse());
  return response;
}

/**
 * Regresa una cadena sin espacios al inicio o al final.
 * @param str la cadena la cual se le eliminarán los espacios.
 * @return str la cadena con el formato solicitado.
 */
std::string RequestManager::trim(const std::string& str){
  size_t first = str.find_first_not_of(" \t\n\r\f\v"); // Find first non-whitespace character
  if (std::string::npos == first) { // If no non-whitespace characters found (string is all whitespace)
    return ""; // Return an empty string
  }
  size_t last = str.find_last_not_of(" \t\n\r\f\v"); // Find last non-whitespace character
  return str.substr(first, (last - first + 1));
}
