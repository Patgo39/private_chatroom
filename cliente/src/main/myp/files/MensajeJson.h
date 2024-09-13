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
  static std::string manejaMensajeCliente(char[], bool&, std::string&);
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
  //Crea el Json para mandar un mensaje general.
  static std::string peticionMandaTextoPublico(char[]);
  //Crea el Json para que el cliente se desconecte.
  static std::string peticionDesconectar();
  //Crea el Json para que el cliente cambie de estado.
  static std::string peticionCambiaEstado(std::vector<std::string>, std::string&);
  //Crea el Json para solicitar la lista de usuarios del chat general.
  static std::string peticionListaGeneral();
  //Crea el Json para mandar un mensaje privado.
  static std::string peticionMensajePrivado(std::vector<std::string>);
  //Crea el Json para crear una sala.
  static std::string peticionCreaCuarto(std::vector<std::string>);
  //Crea el Json para invitar usuarios.
  static std::string peticionInvitaACuarto(std::vector<std::string>);
  //Crea el json para unirse a una cuarto.
  static std::string peticionUnirseCuarto(std::vector<std::string>);
  //Crea el Json para pedir la lista de usuarios.
  static std::string peticionListaCuarto(std::vector<std::string>);
  //Crea el Json para mandar mensajes a un cuarto.
  static std::string peticionMandaMensajeCuarto(std::vector<std::string>);
  //Crea el Json para abandonar un cuarto.
  static std::string peticionAbandonaCuarto(std::vector<std::string>);
  
  //AVISOS
  //Imprime cuando un nuevo usuario se conecta.
  static void avisoNuevoUsuario(Json::Value);
  //Imprime el mensaje del usuario.
  static void avisoTextoPublico(Json::Value);
  //Imprime cuando un usuario se desconeta.
  static void avisoUsuarioDesconectado(Json::Value);
  //Imprime el nuevo estado de un usuario;
  static void avisoNuevoEstado(Json::Value);
  //Imprime la lista general.
  static void avisoListaGeneral(Json::Value);
  //Imprime el texto privado de un usuario.
  static void avisoMensajePrivado(Json::Value);
  //Imprime la solicitud de un usuario para un cuarto.
  static void avisoInvitacion(Json::Value);
  //Imprime el aviso que un usuario se unió al cuarto.
  static void avisoUneACuarto(Json::Value);
  //Imprime la lista de usuarios de un cuarto.
  static void avisoListaCuarto(Json::Value);
  //Imprime el mensaje enviado al cuarto.
  static void avisoTextoCuarto(Json::Value);
  //Imprime la notificación cuando un usuario abandona un cuarto.
  static void avisoAbandonaCuarto(Json::Value);

  //RESPUESTAS
  //Respuesta del servidor de la petición del usuario para identificarse.
  static int respuestaIdentificaUsuario(Json::Value);
  //Respuesta a una petición invalida.
  static int respuestaPeticionInvalida(Json::Value);
  //Respuesta del servidor cuando el usuario del mensaje privado no existe.
  static int respuestaMensajePrivado(Json::Value);
  //Respuesta del servidor cuando el cuarto ya existe o se creó con éxito.
  static int respuestaCrearCuarto(Json::Value);
  //Respuesta del servidor cuando hay un error al invitar usuarios.
  static int respuestaInvitaACuarto(Json::Value);
  //Respuesta del servidor cuando hay un error al unirse a un cuarto.
  static int respuestaUnirseCuarto(Json::Value);
  //Respuesta del servidor cuando hay un error al solicitar la lista del cuarto.
  static int respuestaListaCuarto(Json::Value);
  //Respuesta del servidor cuando hay un error al mandar mensaje al cuarto.
  static int respuestaMandaMensajeCuarto(Json::Value);
  //Respuesta del servidor cuando hay un error al solicitar la lista del cuarto.
  static int respuestaAbandonaCuarto(Json::Value);
  //Respuesta para las peticiones del usuario en un cuarto.
  static int respuestaPeticionCuarto(std::string, std::string);
};
  
#endif
