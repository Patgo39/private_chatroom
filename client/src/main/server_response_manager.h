#ifndef SERVER_RESPONSE_MANAGER_H
#define SERVER_RESPONSE_MANAGER_H

#include <iostream>
#include "message.h"
#include <string>
#include <json/json.h>
#include "server_response_exception.cpp"

class ServerResponseManager{
  Message message;
 public:
  ServerResponseManager();
  Message getMessageFromResponse(std::string serverResponse);

 private:
  Message manageServerResponse(Json::Value value);
  Message manageServerAdvice(Json::Value value);
  
};

#endif
