#include "Usuario.h"

Usuario::Usuario(std::string _nombre, int _usuarioSocket){
  nombre = _nombre;
  usuarioSocket = _usuarioSocket;
}

std::string Usuario::getNombre(){
  return nombre;
}

int Usuario::getSocket(){
  return usuarioSocket;
}

bool Usuario::esIgual(Usuario us){
  return nombre == us.getNombre() && usuarioSocket == us.getSocket();
}
