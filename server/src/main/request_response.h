#ifndef REQUESTRESPONSE_H
#define REQUESTRESPONSE_H

#include <iostream>
#include <cstring>
#include <vector>
#include "room.h"


struct Message{

  enum class MessageType{
    GENERAL = 1, // Se envia a todos los usuarios menos el emisor.
    SPECIFIC = 2, // Uso tanto para mensajes privados como mensajes a usuarios de algun cuarto
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
  // Aviso o mensaje para el cliente o clientes.
  std::vector<Message> messageVector;
  
 public:
  RequestResponse();
  
  std::vector<Message> getMessageVector();
  std::string getUserResponse();
  bool getKeepConection();

  void stopConection();
  void setUserResponse(std::string response);
  void pushGeneralMessage(std::string json);
  void pushSpecificMessage(std::string json, std::vector<int> targetSockets);
  
};
#endif
