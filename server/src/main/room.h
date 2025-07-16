#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "room_exception.cpp"

class Room{
  // Nombre del cuarto
  std::string roomName;
  // Mapa que relaciona el estado del cliente unido/no unido con su socket.
  // Los clientes que estén en el mapa ya están invitados.
  std::map<int, bool> clientMap;

 public:

  Room(std::string _roomName);
  void inviteUser(int clientSocket);
  void setUserToJoined(int clientSocket);
  void eraseUser(int clientSocket);
  bool isUserInList(int clientSocket);
  bool isUserJoined(int clientSocket);
  std::vector<int> getJoinedClients();
};

#endif
