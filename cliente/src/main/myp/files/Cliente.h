#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Cliente{
  bool mantenerConexion;
  int clientSocket;
  int conexion;
  int puerto;
  char buffer[512];
  sockaddr_in serverAddress;

 public:
  Cliente();
  ~Cliente();
  void inicia();
  void cerrarSocket();

 private:
  void setDireccion();
  void conecta();
  void comunicar();
  int lanzaError(std::string, std::string, int);
};

#endif
