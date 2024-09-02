#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <json/json.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Usuario.h"

class Servidor{
  int puerto;
  int serverSocket;
  int conexion;
  std::vector<Usuario> lista;
  sockaddr_in serverAddress;
  char buffer[512];
  int tamBuffer;
  int sizeOfBuffer;
  bool aceptaConexiones;
  std::mutex mtx;

 public:
  Servidor();
  ~Servidor() = default;
  void inicia();
 private:
  void setDireccion();
  int getUsuario(std::string);
  void vincula();
  void escucha();
  void aceptaClientes();
  void manejaCliente(int, bool);
  void desconectaUsuario(Usuario);
  void desconecta();
  int lanzaError(std::string, std::string, int);
  
};

#endif
