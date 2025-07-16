/**
 * @file main.cpp.
 * @brief Punto de entrada para la ejecución del servidor.
 *
 * Punto de entrada para el funcionamiento del servidor en el chatroom.
 * Se crea un objeto Server y se inicia.
 *
 * Author: Patricio García 
 * Year: 2025
 */

#include <iostream>
#include "server.h"

int main(){
  int port;
  const int bufferSize = 1024;
  std::cout<<"Type the port: ";
  std::cin>>port;
  Server s = Server(port, bufferSize);
  s.start();
  return 0;
}
