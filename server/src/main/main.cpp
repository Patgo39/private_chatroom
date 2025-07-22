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
#include <csignal>
#include <memory>
#include "server.h"

std::unique_ptr<Server> globalServer;

void signal_handler(int signum){
  if(signum == SIGINT){
    if(globalServer->hasClients()){
      std::cout<<"Operation rejected, there are still clients connected to the server."<<std::endl;
    }else{
      std::cout<<"Server stopped."<<std::endl;
      globalServer->closeConnection();
    }
  }else if(signum == SIGTSTP){
    std::cout<<"Invalid operation."<<std::endl;
  }
}

int main(){
  int port;
  const int bufferSize = 1024;
  std::cout<<"Type the port: ";
  std::cin>>port;

  globalServer = std::make_unique<Server>(port, bufferSize);
  
  // Señal para CTRL + C
  std::signal(SIGINT, signal_handler);
  // Señal para CTRL + Z
  std::signal(SIGTSTP, signal_handler);
    
  globalServer->start();
  return 0;
}
