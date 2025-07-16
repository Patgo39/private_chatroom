#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <json/json.h>
#include "client.h"
#include "json_controller.h"
#include "request_response.h"
#include "user_status.h"

class RequestManager{
  struct ServerData{
    Client &requester;
    std::map<int,Client> &socketsMap;
    std::map<std::string, Room> &roomMap;

    ServerData(Client &_requester, std::map<int,Client> &_socketsMap, std::map<std::string, Room> &_roomMap) : requester(_requester), socketsMap(_socketsMap), roomMap(_roomMap){}
  };
  
  JsonController jsonController;
public:
  RequestManager();
  RequestResponse getResponse(Client &requester, std::string request, std::map<int, Client> &socketsMap, std::map<std::string, Room> &roomMap);
private:
  RequestResponse manageIdentifyRequest(Json::Value value, ServerData data);
  RequestResponse manageStatusRequest(Json::Value value, ServerData data);
  RequestResponse manageUsersRequest(Json::Value value, ServerData data);
  RequestResponse manageTextRequest(Json::Value value, ServerData data);
  RequestResponse managePublicTextRequest(Json::Value value, ServerData data);
  RequestResponse manageNewRoomRequest(Json::Value, ServerData data);
  // Regresa el objeto respuesta para Jsons incompletos o invalidos.
  RequestResponse getInvalidRequestResponse(ServerData data);
  void eraseClientData(ServerData data);

  std::string trim(const std::string& str);
};

#endif
