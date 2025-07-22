#include "request_response.h"

RequestResponse::RequestResponse(){
  keepConection = true;
  userResponse = "";
}

/**
 * Regresa la respuesta del solicitante.
 * @return userResponse la respuesta del usuario.
 */
std::string RequestResponse::getUserResponse(){
  return userResponse;
}

/**
 * Regresa el estado de la conexión.
 * @return keepConection booleano con el estado de la conexión.
 */
bool RequestResponse::getKeepConection(){
  return keepConection;
}

/**
 * Se actualiza el estado de keepConection a false.
 */
void RequestResponse::stopConection(){
  keepConection = false;
}

/**
 * Se establece la respuesta para el solicitante.
 * @param response la cadena con la respuesta del solicitante.
 */
void RequestResponse::setUserResponse(std::string response){
  userResponse = response;
}

/**
 * Agrega un mensaje general al vector de mensajes.
 * @param json el mensaje json que se agregará al vector.
 */
void RequestResponse::pushGeneralMessage(std::string json){
  messageVector.push_back({json, {}, Message::MessageType::GENERAL});
  
}

/**
 * Agrega un mensaje específico al vector de mensajes.
 * @param json el mensaje json que se agregará al vector.
 * @param sockets el vector de sockets a los cuales se les enviará el mensaje.
 */
void RequestResponse::pushSpecificMessage(std::string json, std::vector<int> sockets){
  messageVector.push_back({json, sockets, Message::MessageType::SPECIFIC});
}

/**
 * Regresa el vector de mensajes.
 * @return messageVector el atributo de la clase con los mensajes.
 */
std::vector<Message> RequestResponse::getMessageVector(){
  return messageVector;
}
