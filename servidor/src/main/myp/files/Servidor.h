#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <json/json.h>
#include <mutex>
#include <thread>
#include <chrono>

class Servidor{
  int puerto;
  int serverSocket;
  int conexion;
  sockaddr_in serverAddress;
  char buffer[512];
  int tamBuffer;
  int sizeOfBuffer;

 public:
  Servidor();
  ~Servidor() = default;
  void inicia();
 private:
  void setDireccion();
  void vincula();
  void escucha();
  void aceptaClientes();
  void manejaCliente(int, bool);
  void desconecta();
  int lanzaError(std::string, std::string, int);
  
};

#endif
