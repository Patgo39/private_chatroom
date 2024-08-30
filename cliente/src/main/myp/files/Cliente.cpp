#include "Cliente.h"

Cliente::Cliente(){
  puerto = _1234;
  buffer[0] = 0;
}

void Cliente::inicia(){
  
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  int  valorLanzaError = lanzaError("Error estableciendo la conexión.", "Conexión del cliente establecida.", clientSocket);
  
  if(valorLanzaError < 0) exit(1);

  
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  lanzaError("No se pudo conectar al servidor.", "Conexión con el servidor establecida.", conexion);
}

int Cliente::lanzaError(std::string mensaje1, std::string mensaje2, int valor){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    return -1;
  }

  std::cout<<mensaje2<<std::endl;
  return 0;
}

void Cliente::cerrarSocket(){
  close(clientSocket);
}
