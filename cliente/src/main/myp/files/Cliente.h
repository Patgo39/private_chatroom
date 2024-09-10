#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <cstring>
#include "MensajeJson.h"
#include "EstadoCliente.h"
#include <atomic>

class Cliente{
  std::string nombre;
  std::string estado;
  int conexion;
  int puerto;
  sockaddr_in serverAddress;

 public:
  Cliente();
  ~Cliente() = default;
  void inicia();
 private:
  void conecta(int);
  void recibeMensaje(int);
  void mandaMensaje(int);
  void desconecta(int);
};

#endif


