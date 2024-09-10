#include "Usuario.h"

Usuario::Usuario(std::string _nombre, int _usuarioSocket){
  nombre = _nombre;
  usuarioSocket = _usuarioSocket;
  estado = EstadoCliente::Estado::ACTIVE;
}

std::string Usuario::getNombre(){
  return nombre;
}

int Usuario::getSocket(){
  return usuarioSocket;
}

std::string Usuario::getEstado(){
  return estado;
}

bool Usuario::esIgual(Usuario us){
  return nombre == us.getNombre() && usuarioSocket == us.getSocket();
}

/**
 * Modifica el estado de un usuario.
 * No se necesita comprobar el estado, porque el servidor lo hace por
 * Nosotros
 *
 * @param nuevoEstado el nuevo estado del usuario.
 */
void Usuario::setEstado(std::string nuevoEstado){
  estado = nuevoEstado;
}
