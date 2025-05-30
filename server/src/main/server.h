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
#include <mutex>
#include <vector>
#include <bits/stdc++.h>
#include "client.h"
#include "request_manager.h"
#include "room.h"
#include "request_response.h"
#include <map>

class Server{
  int port;
  int bufferSize;
  int serverSocket;
  //Vector temporal para almacenar sockets de clientes.
  std::map<int, Client> socketsMap;
  // Relaciona el nombre del cuarto en mayúsculas con el objeto cuarto
  std::map<std::string, Room> roomMap;
  
public:
  Server(int _port, int _bufferSize);
  void start();
  void closeConnection();

private:
  void manageClient(int clientSocket);
  void sendMessageToClient(int clientSocket, std::string data);
  void manageClientRequest(Client client, RequestResponse response);
  void disconnectClient(int clientSocket);
};

#endif
