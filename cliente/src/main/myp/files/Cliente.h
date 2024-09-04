#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>


class Cliente{
  std::string nombre;
  int clientSocket;
  int conexion;
  int puerto;
  std::mutex inmtx;
  std::mutex outmtx;
  //std::condition_variable cv;
  //bool entradaActiva;
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
