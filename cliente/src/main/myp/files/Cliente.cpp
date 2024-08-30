#include "Cliente.h"

Cliente::Cliente(){
  puerto = 1234;
  buffer[0] = 0;
}

void Cliente::inicia(){
  //Se crea el socket.
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  int  valorLanzaError = lanzaError("Error estableciendo la conexión.", "Conexión del cliente establecida.", clientSocket);
  
  if(valorLanzaError < 0){
    cerrarSocket();
    exit(1);
  } 

  setDireccion();
  conecta();
}

void Cliente::setDireccion(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
}

int Cliente::lanzaError(std::string mensaje1, std::string mensaje2, int valor){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    return -1;
  }
  
  std::cout<<mensaje2<<std::endl;
  return 0;
}

void Cliente::conecta(){
  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  int err = lanzaError("No se pudo conectar al servidor.", "Conexión con el servidor establecida.", conexion);

  if(err < 0){
    cerrarSocket();
    exit(1);
  }

  mantenerConexion = true;
}

void Cliente::cerrarSocket(){
  close(clientSocket);
}

void comunicar(){
  
}
