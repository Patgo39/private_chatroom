#ifndef CUARTO_H
#define CUARTO_H

#include <iostream>
#include <string>
#include "Usuario.h"
#include "TipoServidor.h"
#include <json/json.h>
#include <map>
#include <vector>

class Cuarto{
  std::string nombreCuarto;
  std::map<int, bool> mapaUsuarios;
 public:
  //Constructor por defecto.
  Cuarto() = default;
  //Crea un cuarto.
  Cuarto(std::string);
  //Destruye un cuarto.
  ~Cuarto() = default;
  //Regresa el nombre de un cuarto.
  std::string getNombre();
  //Regresa un arreglo de usuarios activos.
  std::vector<int> getVectorUsuarios();
  //Si un usuario ya aceptó la invitación o está invitado, regresa true.
  bool existeUsuario(int);
  //Avisa al cuarto que un usuario ha sido invitado.
  void registraUsuario(int);
  //Avisa al cuarto que un usuario aceptó la invitación.
  void activaUsuario(int);
  //El usuario ya se unió al cuarto.
  bool hayUsuarioUnido(int);
  //Elimina un usuario del mapa.
  void borra(int);
};

#endif
