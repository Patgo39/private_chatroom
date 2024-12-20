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

class Server{
  int port;
  int bufferSize;
  int serverSocket;
  
public:
  Server(int _port, int _bufferSize);
  void start();
  void closeConnection();

private:
  void manageClient(int clientSocket);
  void disconnectClient(int clientSocket);
};

#endif
