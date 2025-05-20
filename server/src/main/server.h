#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <bits/stdc++.h>
#include "client.h"

class Server{
  int port;
  int bufferSize;
  int serverSocket;
  //Vector temporal para almacenar sockets de clientes.
  std::map<int, Client> socketsMap;
  
public:
  Server(int _port, int _bufferSize);
  void start();
  void closeConnection();

private:
  void manageClient(int clientSocket);
  void sendMessageToClient(int clientSocket, std::string data);
  void disconnectClient(int clientSocket);
};

#endif
