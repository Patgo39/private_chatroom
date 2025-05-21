#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstring>
#include <vector>
#include "user_status.h"

class Client{
  int clientSocket;
  std::string userName;
  bool identified;
  UserStatus::Status status;
  // vector para almacenar las salas en las que se encuentra el cliente
  // se reemplazará por una futura clase Room
  std::vector<int> rooms;


public:

  Client(int _clientSocket);
  void setUserName(std::string _userName);
  std::string getUserName();
  void identify();
  int getSocket();
  bool isIdentified();
};


#endif
