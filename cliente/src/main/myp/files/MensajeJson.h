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

public:
  static std::string identificaUsuario(std::string);
  static std::string  manejaMensajeCliente(char[]);
  static int manejaRespuestaServidor(char[]);
private:
  static Json::Value convierteAJson(char[]);
  static std::string convierteACadena(Json::Value);
  static std::vector<std::string> convierteAVector(char[]);
  
  static int respuestaIdentificaUsuario(Json::Value);
  
  static std::string cambiaStatus(std::vector<std::string>);
  static void respuestaCambiaUsuario(Json::Value);

  /* static std::string listaUsuarios(std::vector<std::string>);
  static void respuestaListaUsuarios(Json::Value);

  static std::string mandaTextoPrivado(std::vector<std::string>);
  static void respuestaMandaTextoPrivado(Json::Value);

  static std::string mandaTextoPublico(std::vector<std::string>);

  static std::string creaSala(std::vector<std::string>);
  static void respuestaCreaSala(Json::Value);

  static std::string invita(std::vector<std::string>);
  static void respuestaCreaSala(Json::Value);

  static std::string unirASala(std::vector<std::string>);
  static void respuestaUnirASala(Json::Value);

  static std::string listaUsuariosSala(std::vector<std::string>);
  static void respuestaListaUsuariosSala(Json::Value);

  static std::string textoSala(std::vector<std::string>);
  static void respuestaTextoSala(Json::Value);

  static std::string abandonaSala(std::vector<std::string>);
  static void respuestaAbandonaSala(Json::Value);

  static std::string desconectaUsuario(std::vector<std::string>);*/
};
  
#endif
