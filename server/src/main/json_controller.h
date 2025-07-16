#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include <iostream>
#include <json/json.h>
#include <map>
#include <cstring>
#include <vector>
#include "client.h"
#include "operation.h"


class JsonController{

 public:
  JsonController();

  /**Errores de formato*/
  std::string getInvalidJsonResponse();
  std::string getNotIdentifiedResponse();
  std::string getInvalidRoomNameResponse();

  /**Respuestas para el solicitante de la petición*/
  std::string getIdentificationResponse(std::string username);
  std::string getUsernameAlreadyExistsResponse(std::string username);
  std::string getUsernameMaxCharResponse(std::string username);
  std::string getServerUserListResponse(std::map<int, Client> usersMap);
  std::string getNewRoomCreatedResponse(std::string roomName);
  std::string getRoomAlreadyExistsResponse(std::string roomName); 
  std::string getNoSuchRoomResponse(std::string roomName, Operation::Type type); /**INVITE, JOIN_ROOM, ROOM_USERS, ROOM_TEXT, LEAVE_ROOM*/
  std::string getNoSuchUserResponse(std::string username, Operation::Type type); /**TEXT, INVITE */
  std::string getJoinRoomSuccessResponse(std::string roomName);
  std::string getNotInvitedResponse(std::string roomName, Operation::Type type); /**JOIN_ROOM, */
  std::string getNotJoinedResponse(std::string roomName, Operation::Type type);/**ROOM_TEXT, ROOM_USERS, LEAVE_ROOM*/
  std::string getRoomUsersResponse(std::vector<Client> roomUsers);

  /**Mensajes generales*/
  std::string getNewUserAdvice(std::string username);
  std::string getNewStatusAdvice(Client client);
  std::string getPrivateTextAdvice(std::string username, std::string message);
  std::string getPublicTextAdvice(std::string username, std::string message);
  std::string getInvitationAdvice(std::string username, std::string roomName);
  std::string getUserJoinedRoomAdvice(std::string username, std::string roomName);
  std::string getRoomTextAdvice(std::string username, std::string roomName, std::string message);
  std::string getLeftRoomAdvice(std::string username, std::string roomName);
  std::string getUserDisconnectedAdvice(std::string username);
  
  

 private:
  std::string turnJsonToString(Json::Value json);
};

#endif
