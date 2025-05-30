#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "client.h"
#include <string>
#include <map>
#include <vector>

class Room{

  std::string roomName;
  std::map<bool, Client> clientMap;

 public:

  Room();
  void inviteUser(Client client);
};

#endif
