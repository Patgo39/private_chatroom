#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "client_connection_exception.cpp"

class Client{
  int port;
  int bufferSize;
  std::string ipAddress;
  int clientSocket;
 public:
  
  Client(int _port, int _bufferSize, std::string _ipAddress);
  void start();
  void sendMessage(std::string);
  std::string receiveMessages();
  void closeConection();
};

#endif
