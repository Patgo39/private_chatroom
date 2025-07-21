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
  // Agrega un usuario al mapa de clientes.
  void inviteUser(int clientSocket);
  // Marca un usuario como unido.
  void setUserToJoined(int clientSocket);
  // Borra un usuario del mapa de clientes.
  void eraseUser(int clientSocket);
  // Si el cliente está en la lista regresa true. False e.o.c.
  bool isUserInList(int clientSocket);
  // Regresa true si el cliente está en la lista y unido.
  bool isUserJoined(int clientSocket);
  // Regresa un vector de sockets con los clientes unidos.
  std::vector<int> getJoinedClients();
};

#endif
