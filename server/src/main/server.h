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

class Server{
  int port;
  int bufferSize;
  int serverSocket;
  

  Server(int _port, int _bufferSize);

  void start();
  void closeConnection();
};

#endif
