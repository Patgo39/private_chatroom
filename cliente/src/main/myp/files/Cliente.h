#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
//#include <limits>
#include <thread>

class Cliente{
  std::string nombre;
  int clientSocket;
  int conexion;
  int puerto;
  sockaddr_in serverAddress;

 public:
  Cliente();
  ~Cliente() = default;
  void inicia();
 private:
  void conecta();
  void recibeMensaje();
  void mandaMensaje();
  void desconecta();
  void lanzaError(std::string, std::string, int, bool);
};

#endif
