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
#include <map>
#include <random>

/*
 *Comandos del usuario:
 * REQUEST -s "new_status"  // STATUS Cambia el estado del usuario
 * REQUEST -u // USERS Obtiene la lista de usuarios.
 * REQUEST -t "Nombre del usuario" texto ...  //TEXT Envía un texto privado.
 * REQUEST -nr "Nombre de la sala" //NEW_ROOM Crea una sala
 * REQUEST -i  "nombre de la sala" "usuario1" "usuario2" "usuario3" ... //INVITE Invita usuarios a una sala.
 * REQUEST -jr "Nombre de la sala"   //JOIN_ROOM El usuario se une a una sala.
 * REQUEST -ru  //ROOM_USERS Pide la lista de usuarios de la sala
 * REQUEST -lr "Nombre de la sala" //LEAVE_ROOM el usuario abandona la sala
 * REQUEST -d //DISCONNECT Desconecta al usuario
 */

class MensajeJson{ 
  static std::map<std::string, int> coloresUsuarios;
  static int contador;
  static std::string finColor;
public:
  //Crea el Json para identificarse con el servidor.
  static std::string peticionIdentificaUsuario(std::string);
  //Crea el Json para la petición del cliente al servidor.
  static std::string manejaMensajeCliente(char[], bool&);
  //Maneja la respuesta del servidor a la petición del cliente.
  static int manejaRespuestaServidor(char[]);
  //Maneja los avisos del Servidor.
  static void manejaAvisoServidor(char []);
  
private:
  //Regresa un color.
  static std::string getColor(int i);
  //Regresa un indice para el color.
  static int getIndice();
  //Revisa si un usuario ya está en el mapa de colores.
  static bool existeUsuario(std::string);
  //Regresa un número aleatorio de minimo 1 y máximo 256.
  static int getAleatorio();
  //Convierte un arreglo de caracteres a Json.
  static Json::Value convierteAJson(char[]);
  //Convierte un Json a cadena.
  static std::string convierteACadena(Json::Value);
  //Convierte un arreglo de caracteres a vector.
  static std::vector<std::string> convierteAVector(char[]);

  //PETICIONES
  //Crea la petición Json para cambiar el estatus del usuario.
  static std::string peticionCambiaStatus(std::vector<std::string>);
  //Crea el Json para mandar un mensaje general.
  static std::string peticionMandaTextoPublico(char[]);
  //Crea el Json para que el cliente se desconecte.
  static std::string peticionDesconectar();
  
  //AVISOS
  //Imprime cuando un nuevo usuario se conecta.
  static void avisoNuevoUsuario(Json::Value);
  //Imprime el mensaje del usuario.
  static void avisoTextoPublico(Json::Value);
  //Imprime cuando un usuario se desconeta.
  static void avisoUsuarioDesconectado(Json::Value);

  //RESPUESTAS
  //Respuesta del servidor de la petición del usuario para identificarse.
  static int respuestaIdentificaUsuario(Json::Value);
  //Respuesta del servidor de la petición del usuario para cambiar su estatus.
  static void respuestaCambiaStatus(Json::Value);
};
  
#endif
