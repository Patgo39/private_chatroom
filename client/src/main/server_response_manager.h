#ifndef SERVER_RESPONSE_MANAGER_H
#define SERVER_RESPONSE_MANAGER_H

#include <iostream>
#include "message.h"
#include <string>
#include <json/json.h>
#include "server_response_exception.cpp"

class ServerResponseManager{

 public:
  ServerResponseManager();
  Message getMessageFromResponse(std::string serverResponse);

 private:
  
  
};

#endif
