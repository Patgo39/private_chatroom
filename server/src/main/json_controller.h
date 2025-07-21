#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include <iostream>
#include <json/json.h>
#include <map>
#include <cstring>
#include <vector>
#include "client.h"
#include "operation.h"
#include "invalid_operation_exception.cpp"


class JsonController{

 public:
  JsonController();

  /**Errores de formato*/
  // Crea un json para notificar un error de formato.
  std::string getInvalidJsonResponse();
  // Crea un Json para notificar al cliente que aún no se identifica.
  std::string getNotIdentifiedResponse();
  // Crea un json si el nombre del cuarto no tiene formato adecuado.
  std::string getNewRoomMaxCharResponse(std::string roomName);
  // Crea un json si el nombre de usuario no tiene formato adecuado.
  std::string getUsernameMaxCharResponse(std::string username);

  /**Respuestas para el solicitante de la petición*/
  // Crea el Json para la respuesta de identificacion.
  std::string getIdentificationResponse(std::string username);
  // Crea el json que informa que el nombre de usuario ya existe.
  std::string getUsernameAlreadyExistsResponse(std::string username);
  // Crea el json con la lista de usuarios.
  std::string getServerUserListResponse(std::map<int, Client> usersMap);
  // Crea el json de confirmación de creación de un cuarto.
  std::string getNewRoomCreatedResponse(std::string roomName);
  // Crea el json para notificar al cliente que el cuarto ya existe.
  std::string getRoomAlreadyExistsResponse(std::string roomName);
  // Crea el json que notifica al cliente que el cuarto no existe.
  std::string getNoSuchRoomResponse(std::string roomName, Operation::Type type);
  // Crea el json que notifica al cliente que un usuario no existe.
  std::string getNoSuchUserResponse(std::string username, Operation::Type type); 
  // Crea el json de confirmación de unión a un cuarto.
  std::string getJoinRoomSuccessResponse(std::string roomName);
  // Crea el json que notifica al usuario que no ha sido invitado a un cuarto.
  std::string getNotInvitedResponse(std::string roomName);
  // Crea el json que notifica al cliente que aún no se une al cuarto.
  std::string getNotJoinedResponse(std::string roomName, Operation::Type type);
  // Crea un json con la lista de clientes en un cuarto.
  std::string getRoomUsersResponse(std::string roomName, std::vector<Client> roomUsers);

  /**Avisos generales*/
  // Crea el json que informa de la unión de un nuevo cliente.
  std::string getNewUserAdvice(std::string username);
  // Crea el json que notifica el cambio de estado de un cliente.
  std::string getNewStatusAdvice(Client client);
  // Crea el json con un mensaje privado.
  std::string getPrivateTextAdvice(std::string username, std::string message);
  // Crea el json con un mensaje público.
  std::string getPublicTextAdvice(std::string username, std::string message);
  // Crea el json que notifica a un cliente si fue invitado a un cuarto.
  std::string getInvitationAdvice(std::string username, std::string roomName);
  // Crea el json que notifica de la unión de un cliente a un cuarto.
  std::string getUserJoinedRoomAdvice(std::string username, std::string roomName);
  // Crea el json con un mensaje para un cuarto.
  std::string getRoomTextAdvice(std::string username, std::string roomName, std::string message);
  // Crea el json que notifica a clientes de un cuarto si alguien se desconectó
  std::string getLeftRoomAdvice(std::string username, std::string roomName);
  // Crea el json que avisa a los demás clientes que un cliente se desconectó.
  std::string getUserDisconnectedAdvice(std::string username);
  
  

 private:
  // Convierte un json a cadena.
  std::string turnJsonToString(Json::Value json);
};

#endif
