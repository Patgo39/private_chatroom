#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include "EstadoCliente.h"

class Usuario{
  std::string nombre;
  int usuarioSocket;
  std::string estado;
 public:
  Usuario() = default;
  Usuario(std::string, int);
  std::string getNombre();
  int getSocket();
  std::string getEstado();
  void setEstado(std::string);
  bool esIgual(Usuario us);
};

#endif
