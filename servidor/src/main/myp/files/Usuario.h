#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

class Usuario{
  std::string nombre;
  int usuarioSocket;
 public:
  Usuario() = default;
  Usuario(std::string, int);
  std::string getNombre();
  int getSocket();
  bool esIgual(Usuario us);
};

#endif
