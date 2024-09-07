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
#include <map>
#include "ManejaPeticionCliente.h"
#include "TipoCliente.h"

class Servidor{
  int puerto;
  int serverSocket;
  int conexion;
  std::map<int, Usuario> mapa;
  sockaddr_in serverAddress;
  std::mutex mtx;

 public:
  Servidor();
  ~Servidor() = default;
  void inicia();
 private:
  int getUsuario(std::string);
  void vincula();
  void conectaClientes();
  void mandaMensaje(Usuario, char[]);
  void manejaCliente(int);
  void desconectaUsuario(int);
  void desconecta();
  void lanzaError(std::string, std::string, int, bool);
  std::string manejaPeticion(char[], bool&, std::string&);
};

#endif
