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
  Cliente(int);
  ~Cliente();
  void solicitarConexion();
  void cerrarSocket();
  void enviaDatos();

 private:
  int lanzaError(std::string, std::string, int);
};
