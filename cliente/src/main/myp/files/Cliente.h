#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Cliente{
  
  int clientSocket;
  int conexion;
  int puerto;
  char buffer[512];

 public:
  Cliente();
  ~Cliente();
  void inicia();
  void cerrarSocket();

 private:
  int lanzaError(std::string, std::string, int);
};

#endif
