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
  std::vector<std::string> rooms;


public:

  Client(int _clientSocket);
  void setUserName(std::string _userName);
  void setUserStatus(UserStatus::Status _status);
  
  std::string getUserName();
  std::string getUserStatus();
  int getSocket();
  std::vector<std::string> getRoomVector();
  
  void identify();
  bool isIdentified();
  void joinToRoom(std::string roomName);
  void forgetRoom(std::string roomName);
  
  
};


#endif
