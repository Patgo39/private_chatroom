#include "json_controller.h"

JsonController::JsonController(){
}

/**Errores de formato*/

/**
 * Se construye el json para notificar al cliente que el formato del json que envió es
 * incorrecto.
 * @return json construido convertido a cadena.
 */
std::string JsonController::getInvalidJsonResponse(){
  Json::Value json;
  json["type"] = "RESPONSE";
  json["operation"] = "INVALID";
  json["result"] = "INVALID";

  return turnJsonToString(json);
}

/**
 * Construye el json para notificar al cliente que aún no se ha identificado.
 * @return json el json construido convertido a cadena.
 */
std::string JsonController::getNotIdentifiedResponse(){
  Json::Value json;
  json["type"] = "RESPONSE";
  json["operation"] = "INVALID";
  json["result"] = "NOT_IDENTIFIED";

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica al cliente si su nombre de usuario supera los 8
 * caracteres.
 * @param username el nombre de usuario que incumple con el formato requerido.
 * @return el json construido convertido a cadena.
 */
std::string JsonController::getUsernameMaxCharResponse(std::string username){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "NAME_TOO_LONG";
  json["extra"] = username;

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica al cliente que el nombre de cuarto proporcionado para
 * crear un cuarto supera los 16 caracteres.
 * @param roomName el nombre de cuarto que incumple el formato requerido.
 * @return el json convertido a cadena.
 */
std::string JsonController::getNewRoomMaxCharResponse(std::string roomName){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "NEW_ROOM";
  json["result"] = "NAME_TOO_LONG";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**Respuestas para el solicitante de la petición*/

/**
 * Se construye el json que notifica al cliente que su petición de identificación fue
 * exitosa.
 * @param username el nombre de usuario del cliente que se identificó correctamente.
 * @return el json construido a cadena.
 */
std::string JsonController::getIdentificationResponse(std::string username){
  Json::Value json;

  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "SUCCESS";
  json["extra"] = username;
  
  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica al cliente si el nombre de usuario que proporcionó
 * para identificarse ya está siendo ocupado por otro cliente conectado.
 * @param username el nombre de usuario ocupado.
 * @return el json contruido a cadena.
 */
std::string JsonController::getUsernameAlreadyExistsResponse(std::string username){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "IDENTIFY";
  json["result"] = "USER_ALREADY_EXISTS";
  json["extra"] = username;

  return turnJsonToString(json);
}

/**
 * Se construye el json con la lista de usuarios conectados que el cliente solicitó.
 * @param userMap el mapa de usuarios del servidor.
 * @return el json convertido a cadena.
 */
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

/**
 * Se construye el json que notifica al cliente que su petición de crear un nuevo cuarto
 * fue exitosa.
 * @param roomName el nombre del cuarto creado por el usuario.
 * @return el json convertido a cadena.
 */
std::string JsonController::getNewRoomCreatedResponse(std::string roomName){
  Json::Value json;
  json["type"] = "RESPONSE";
  json["operation"] = "NEW_ROOM";
  json["result"] = "SUCCESS";
  json["extra"] = roomName;
  
  return turnJsonToString(json);
}

/**
 * Se construye el json para notificar al cliente que el nombre de cuarto que solicita
 * crear ya existe.
 * @param roomName el nombre del cuarto que ya existe.
 * @return el json convertido a cadena.
 */
std::string JsonController::getRoomAlreadyExistsResponse(std::string roomName){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "NEW_ROOM";
  json["result"] = "ROOM_ALREADY_EXISTS";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json para notificar al cliente que el cuarto en el que intenta hacer
 * alguna solicitud no existe. Las operaciones válidas para esta función son: INVITE,
 * JOIN_ROOM, ROOM_USERS, ROOM_TEXT, LEAVE_ROOM.
 * @param roomName el nombre del cuarto que no existe.
 * @param type el tipo de operación que el cliente solicitó.
 * @return el json convertido a cadena.
 * @throw InvalidOperationException si la función recibe una operación inválida.
 */
std::string JsonController::getNoSuchRoomResponse(std::string roomName, Operation::Type type){
  Json::Value json;

  if(type == Operation::Type::TEXT){
    throw InvalidOperationException("");
  }

  std::string operation = Operation::getStringFromType(type);
  
  json["type"] = "RESPONSE";
  json["operation"] = operation;
  json["result"] = "NO_SUCH_ROOM";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json para notificar al cliente que el usuario que invitó a un cuarto o
 * le envió un mensaje privado no existe. Las operaciones válidas para esta función son:
 * TEXT, INVITE.
 * @param username el nombre de usuario del cliente que no existe.
 * @param type el tipo de operación que el cliente solicitó.
 * @return el json convertido a cadena.
 * @throw InvalidOperationException si la función recibe una operación inválida.
 */
std::string JsonController::getNoSuchUserResponse(std::string username, Operation::Type type){

  std::string operation;
  
  switch(type){
  case Operation::Type::INVITE: operation = "INVITE"; break;
  case Operation::Type::TEXT: operation = "TEXT"; break;
  default: throw InvalidOperationException("");
  }
  
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = operation;
  json["result"] = "NO_SUCH_USER";
  json["extra"] = username;

  return turnJsonToString(json);
}

/**
 * Se construye el json para notificar que un cliente se unió exitosamente
 * a un cuarto.
 * @param roomName el nombre del cuarto al que el cliente se unió.
 * @return el json convertido a cadena.
 */
std::string JsonController::getJoinRoomSuccessResponse(std::string roomName){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "JOIN_ROOM";
  json["result"] = "SUCCESS";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica al cliente que aún no ha sido invitado
 * a un cuarto.
 * @param roomName el nombre del cuarto al que el cliente no se ha unido.
 * @return el json convertido a cadena.
 */
std::string JsonController::getNotInvitedResponse(std::string roomName){
  Json::Value json;
  
  json["type"] = "RESPONSE";
  json["operation"] = "JOIN_ROOM";
  json["result"] = "NOT_INVITED";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json para notificar al cliente que aún no ha sido invitado
 * a un cuarto en el que intenta hacer alguna petición. Las operaciones
 * válidas para esta función son: ROOM_TEXT, ROOM_USERS, LEAVE_ROOM, INVITE.
 * @param roomName el nombre del cuarto al que el cliente aún no ha sido
 * invitado.
 * @param type el tipo de operación válido para esta función.
 * @return el json convertido a cadena.
 * @throw InvalidOperationException si la función recibe una operación
 * inválida.
 */
std::string JsonController::getNotJoinedResponse(std::string roomName, Operation::Type type){
  Json::Value json;
  std::string operation;

  switch(type){
  case Operation::Type::JOIN_ROOM:
  case Operation::Type::TEXT: throw InvalidOperationException("");
  default: break;
  }

  operation = Operation::getStringFromType(type);
  
  json["type"] = "RESPONSE";
  json["operation"] = operation;
  json["result"] = "NOT_JOINED";
  json["extra"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json con la lista de clientes en un cuarto al que el
 * usuario ya se encuentra unido.
 * @param roomName el nombre del cuarto de cual se obtendrá la lista.
 * @param roomUsers un vector con los clientes del cuarto.
 * @return el json convertido a cadena.
 */
std::string JsonController::getRoomUsersResponse(std::string roomName, std::vector<Client> roomUsers){
  Json::Value json;
  Json::Value users;

  for(Client c : roomUsers){

    users[c.getUserName()] = c.getUserStatus();
  }
  
  json["type"] = "ROOM_USER_LIST";
  json["roomname"] = roomName;
  json["users"] = users;

  return turnJsonToString(json);
}


  /**Avisos generales*/

/**
 * Se construye el json que notifica a todos los clientes del chat que un
 * nuevo usuario se ha identificado.
 * @param username el nombre del usuario recien conectado.
 * @return el json convertido a string.
 */
std::string JsonController::getNewUserAdvice(std::string username){
  Json::Value json;

  json["type"] = "NEW_USER";
  json["username"] = username;

  return turnJsonToString(json);

}

/**
 * Se construye el json que notifica a todos los clientes del chat que un
 * cliente ha actualizado su status.
 * @param client el cliente que actualizó su estado.
 * @return el json convertido a cadena.
 */
std::string JsonController::getNewStatusAdvice(Client client){
  Json::Value json;

  json["type"] = "NEW_STATUS";
  json["username"] = client.getUserName();
  json["status"] = client.getUserStatus();

  return turnJsonToString(json);
}

/**
 * Se construye el json con un mensaje para un cliente en específico.
 * @param username el nombre del usuario que mandó un mensaje privado.
 * @param message una cadena con el mensaje privado.
 * @return el json convertido a cadena.
 */
std::string JsonController::getPrivateTextAdvice(std::string username, std::string message){
  Json::Value json;

  json["type"] = "TEXT_FROM";
  json["username"] = username;
  json["text"] = message;

  return turnJsonToString(json);
}

/**
 * Se construye el json que contiene un mensaje general.
 * @param username el nombre de usuario que envió el mensaje.
 * @param message el mensaje público.
 * @return el json convertido a cadena.
 */
std::string JsonController::getPublicTextAdvice(std::string username, std::string message){
  
  Json::Value json;

  json["type"] = "PUBLIC_TEXT";
  json["text"] = message;

  return turnJsonToString(json);
}

/**
 * Se construye el json con una invitación de unión a un cuarto.
 * @param username el nombre del usuario que envió la invitación.
 * @param roomName el nombre del cuarto al que se está invitando.
 * @return el json convertido a cadena.
 */
std::string JsonController::getInvitationAdvice(std::string username, std::string roomName){
  Json::Value json;
  json["type"] = "INVITATION";
  json["username"] = username;
  json["roomname"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica a los clientes de un cuarto cuando un
 * nuevo usuario se une.
 * @param username el nombre del usuario que recien se unió.
 * @param roomName el nombre del cuarto al que se unió el usuario.
 * @return el json convertido a cadena.
 */
std::string JsonController::getUserJoinedRoomAdvice(std::string username, std::string roomName){
  Json::Value json;
  json["type"] = "JOINED_ROOM";
  json["username"] = username;
  json["roomname"] = roomName;

  return turnJsonToString(json);
}

/**
 * Se construye el json con el mensaje para un cuarto.
 * @param username el nombre del ususario que envió el mensaje.
 * @param roomName el nombre del cuarto que recibirá el mensaje.
 * @param message el mensaje para el cuarto.
 * @return el json convertido a cadena.
 */
std::string JsonController::getRoomTextAdvice(std::string username, std::string roomName, std::string message){
  Json::Value json;
  json["type"] = "ROOM_TEXT_FROM";
  json["roomname"] = roomName;
  json["username"] = username;
  json["text"] = message;

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica a los clientes en un cuarto que alguien
 * abandonó.
 * @param username el nombre del usuario que salió de un cuarto.
 * @param roomName el nombre del cuarto del que el usuario salió.
 * @return el json convertido a cadena.
 */
std::string JsonController::getLeftRoomAdvice(std::string username, std::string roomName){

  Json::Value json;

  json["type"] = "LEFT_ROOM";
  json["roomname"] = roomName;
  json["username"] = username;

  return turnJsonToString(json);
}

/**
 * Se construye el json que notifica a todos los clientes que un usuario
 * abandonó el chat.
 * @param username el nombre del usuario que abandonó el chat.
 * @return el json convertido a cadena.
 */
std::string JsonController::getUserDisconnectedAdvice(std::string username){

  Json::Value json;

  json["type"] = "DISCONNECTED";
  json["username"] = username;

  return turnJsonToString(json);
}

/**
 * Se convierte un objeto json a una cadena.
 * @return output el json convertido a cadena.
 */
std::string JsonController::turnJsonToString(Json::Value json){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, json);
  return output;
}
