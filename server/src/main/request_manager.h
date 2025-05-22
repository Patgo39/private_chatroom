#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <string>
#include <json/json.h>
#include "client.h"

class RequestManager{
  
public:
  RequestManager();
  void getResponse(Client requester, std::string request);
   
};

#endif
