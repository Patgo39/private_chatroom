#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
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
  bool stop_listening; // Variable booleana que indica si se escucha al servidor.
  std::string buffer_string;
  std::condition_variable cv;
  std::mutex mtx;
  std::thread listening_thread;
  
 public:
  
  Client(int _port, int _bufferSize, std::string _ipAddress);
  void start();
  void sendMessage(std::string);
  std::string receiveMessages();
  void closeConnection();

private:
  void onServerMessageEvent();
};

#endif
