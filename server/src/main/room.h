#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "client.h"
#include <string>
#include <map>

class Room{

  std::string roomName;
  std::map<bool, Client> clientMap;

 public:

  Room();
  
};

#endif
