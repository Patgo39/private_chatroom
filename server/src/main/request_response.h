#ifndef REQUESTRESPONSE_H
#define REQUESTRESPONSE_H

#include <iostream>
#include <cstring>
#include <vector>
#include "room.h"


struct Message{

  // Enumeración para el tipo de mensaje que puede haber.
  enum class MessageType{
    GENERAL, // Se envia a todos los usuarios menos el emisor.
    SPECIFIC, // Uso tanto para mensajes privados como mensajes a usuarios de algun cuarto
    NONE
  };
  
  // Mensaje para los usuarios.
  std::string message;
  // Vector con el nombre de usuarios objetivo, si es que es el caso.
  std::vector<int> targetSockets;
  // Tipo del mensaje.
  MessageType type;
};

class RequestResponse{
  // True para mantener la conexión del cliente, false para desconectar.
  bool keepConection;
  // Respuesta para el usuario
  std::string userResponse;
  // Vector de mensajes para los demás clientes.
  std::vector<Message> messageVector;
  
 public:
  RequestResponse();
  // Regresa el vector de mensajes.
  std::vector<Message> getMessageVector();
  // Regresa la respuesta del solicitante.
  std::string getUserResponse();
  // Regresa el estado de la conexión.
  bool getKeepConection();
  // Detiene la conexión del cliente.
  void stopConection();
  // Se establece la respuesta del solicitante.
  void setUserResponse(std::string response);
  // Agrega un nuevo mensaje general al vector de mensajes.
  void pushGeneralMessage(std::string json);
  // Agrega un nuevo mensaje específico al vector de mensajes.
  void pushSpecificMessage(std::string json, std::vector<int> targetSockets);
  
};
#endif
