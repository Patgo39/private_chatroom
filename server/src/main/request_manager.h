#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <string>
#include <json/json.h>
#include "client.h"
#include "json_controller.h"
#include "request_response.h"
#include "user_status.h"

class RequestManager{
  JsonController jsonController;
public:
  RequestManager();
  RequestResponse getResponse(Client &requester, std::string request, std::map<int, Client> &socketsMap, std::map<std::string, Room> &roomMap);
private:
  RequestResponse manageIdentifyRequest(Json::Value value, Client &requester, std::map<int, Client> &socketsMap);
  RequestResponse manageStatusRequest(Json::Value value, Client &requester);
  // Regresa el objeto respuesta para Jsons incompletos o invalidos.
  RequestResponse getInvalidRequestResponse();
};

#endif
