/**
 * @file server.h
 * @brief El servidor administra clientes y maneja las respuestas a sus peticiones.
 *
 *
 * El servidor tiene un hilo principal el cual se encarga de aceptar o rechazar
 * las peticiones de los usuarios para unirse al chat. Cuando se une un nuevo
 * cliente, se crea un hilo nuevo que administra todas las peticiones de dicho
 * cliente.
 */



#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <bits/stdc++.h>
#include "client.h"
#include "request_manager.h"
#include "room.h"
#include "request_response.h"
#include <map>

class Server{
  int port; // Puerto dónde se esperan clientes
  int bufferSize; // Tamaño del buffer de entrada
  int serverSocket;  // EL socket para aceptar nuevos usuarios.
  std::map<int, Client> socketsMap; // Mapa que relaciona el socket con un objeto cliente.
  // Relaciona el nombre del cuarto con el objeto cuarto
  std::map<std::string, Room> roomMap;
  // Estado del servidor
  bool connected;
  
public:
  Server(int _port, int _bufferSize);
  // Inicia el funcionamiento del servidor.
  void start();
  // Cierra el socket del servidor.
  void closeConnection();
  // Regresa true si hay clientes conectados y false en otro caso.
  bool hasClients();

private:
  // Administra las peticiones del cliente.
  void manageClient(int clientSocket);
  // Manda un mensaje a un cliente dado su socket.
  void sendMessageToClient(int clientSocket, std::string data);
  // En base a la petición del cliente, se realiza una acción de acuerdo a esta.
  void manageClientRequest(Client client, RequestResponse response);
  // Desconecta un cliente dado su socket.
  void disconnectClient(int clientSocket);
};

#endif
