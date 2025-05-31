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
    NONMESSAGE = 3 // NO hay mensaje para los demás usuarios.
  };
  
  // Mensaje para los usuarios.
  std::string message;
  // El nombre del cuarto si es que el mensaje es para algún cuarto.
  std::string roomName;
  // Vector con el nombre de usuarios objetivo, si es que es el caso.
  std::vector<int> targetsockets;
  // Tipo del mensaje.
  MessageType type;
};

class RequestResponse{
  // True para mantener la conexión del cliente, false para desconectar.
  bool keepConection;
  // Respuesta para el usuario
  std::string userResponse;
  // Mensaje general
  Message message;
  
 public:
  RequestResponse();
  
  Message getPublicMessage();
  std::string getUserResponse();
  bool getKeepConection();

  void stopConection();
  void setUserResponse(std::string response);
  void setGeneralMessage(std::string json);
  void setSpecificMessage(std::string json, std::vector<int> targetSockets);
};
#endif
