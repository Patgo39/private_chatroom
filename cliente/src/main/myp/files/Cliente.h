#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <cstring>


class Cliente{
  std::string nombre;
  int conexion;
  int puerto;
  sockaddr_in serverAddress;
  std::thread tSend, tRec;

 public:
  Cliente();
  ~Cliente() = default;
  void inicia();
 private:
  void conecta(int);
  void recibeMensaje(int);
  void mandaMensaje(int);
  void desconecta(int);
  void lanzaError(std::string, std::string, int, bool, int);
};

#endif


