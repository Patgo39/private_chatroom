/*
 * La clase servidor se encarga de iniciar la conexión, aceptar conexiones de
 * los clientes y manejar las peticiones que estos hagan al servidor.
 * Para manejar las peticiones, el servidor se auxilia de la clase
 * ManejaPeticionCliente.
 */

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <json/json.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Usuario.h"
#include <map>
#include "ManejaPeticionCliente.h"
#include "TipoCliente.h"
#include "Cuarto.h"

class Servidor{
  int puerto;
  int serverSocket;
  int conexion;
  std::map<int, Usuario> mapa;
  std::vector<Cuarto> cuartos;
  sockaddr_in serverAddress;
  std::mutex mtx;

 public:
  //Constructor de la clase.
  Servidor();
  
  //Destructor de la clase.
  ~Servidor() = default;
  
  //Inicia el funcionamiento del servidor.
  void inicia();
  
 private:
  //Identifica al usuario y lo agrega al mapa de clientes.
  bool identificarUsuario(int);
  
  //Vincula el socket del servidor.
  void vincula();
  
  //Escucha y acepta clientes.
  void conectaClientes();
  
  //Manda mensaje a todos los usuarios, excepto al usuario que se recibe.
  void mandaMensajeGeneral(int, std::string);
  
  //Manda mensaje al usuario especificado.
  void mandaMensajeIndividual(int, std::string);
  
  //Se recibe un mensaje de un usuario.
  std::string recibeMensaje(int);
  
  //Maneja la comunicación con el usuario.
  void manejaCliente(int);
  
  //Desconecta a un usuario por solicitud.
  void desconectaUsuario(int);
  
  //Desconecta el servidor.
  void desconecta();
  
  //Lanza un mensaje cuando hay un error.
  void lanzaError(std::string, std::string, int, bool);
  
  //Contempla todas las posibles peticiones que el usuario pueda hacer.
  void manejaPeticion(std::string, int);
};

#endif
