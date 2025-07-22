#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstring>
#include <vector>
#include "user_status.h"

class Client{
  // El socket del cliente.
  int clientSocket;
  // El nombre de usuario del cliente.
  std::string userName;
  // Booleano con el valor que indica si el cliente ya se identificó.
  bool identified;
  // Status del cliente.
  UserStatus::Status status;
  // vector para almacenar las salas en las que se encuentra el cliente
  std::vector<std::string> rooms;


public:

  Client(int _clientSocket);
  // Establece el nombre de usuario de un cliente.
  void setUserName(std::string _userName);
  // Establece el estado de un cliente.
  void setUserStatus(UserStatus::Status _status);

  // Regersa el nombre de usuario establecido.
  std::string getUserName();
  // Regresa el estado del cliente.
  std::string getUserStatus();
  // Regresa el socket del cliente.
  int getSocket();
  // Regersa el vector de cuartos a los que el cliente se ha unido.
  std::vector<std::string> getRoomVector();

  // Marca al usuario como identificado.
  void identify();
  // Regesa true si el cliente ya se identificó.
  bool isIdentified();
  // Agrega un nuevo cuarto al vector de cuartos.
  void joinToRoom(std::string roomName);
  // Elimina un cuarto del vector de cuartos.
  void forgetRoom(std::string roomName);
  
  
};


#endif
