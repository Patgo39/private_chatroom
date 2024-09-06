#ifndef MENSAJEJSON_H
#define MENSAJEJSON_H

#include <iostream>
#include <json/json.h>
#include <string>
#include "TipoCliente.h"
#include "TipoServidor.h"
#include "ResultadoServidor.h"
#include <vector>
#include <sstream>
#include <unordered_map>

/*
 *Comandos del usuario:
 * request -s "new_status"  // STATUS Cambia el estado del usuario
 * request -u // USERS Obtiene la lista de usuarios.
 * request -t "Nombre del usuario" texto ...  //TEXT Envía un texto privado.
 * request -nr "Nombre de la sala" //NEW_ROOM Crea una sala
 * request -i  "nombre de la sala" "usuario1" "usuario2" "usuario3" ... //INVITE Invita usuarios a una sala.
 * request -jr "Nombre de la sala"   //JOIN_ROOM El usuario se une a una sala.
 * request -ru  //ROOM_USERS Pide la lista de usuarios de la sala
 * request -lr "Nombre de la sala" //LEAVE_ROOM el usuario abandona la sala
 * request -d //DISCONNCT Desconecta al usuario
 */

class MensajeJson{
  /*enum Banderas {
    S = 0,
    U = -1,
    T = -2,
    NR = -3,
    I = -4,
    JR = -5,
    RU = -6,
    LR = -7,
    D = -8
  };
  const std::unordered_map<std::string, Banderas> listaBanderas ={
    {"-s", S},
    {"-u", U},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
  };*/
public:
  static void identificaUsuario(std::string);
  static void manejaMensajeCliente(char[]);
  static void manejaMensajeServidor(char[]);
private:
  static Json::Value convierteAJson(char[]);
  static std::string convierteACadena(Json::Value);
  static std::vector<std::string> convierteAVector(char[]);
  
};
  
#endif
