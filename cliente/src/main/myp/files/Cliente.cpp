#include "Cliente.h"

Cliente::Cliente(int _puerto){
  puerto = _puerto;
  buffer[0] = 0;
  
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  int valorLanzaError;
  
  valorLanzaError = lanzaError("Error estableciendo la conexión.", "Conexión del cliente establecida.", clientSocket);
  if(valorLanzaError == -1) exit(1);
}

void Cliente::solicitarConexion(){
  
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

void Cliente::enviaDatos(){
  
}
