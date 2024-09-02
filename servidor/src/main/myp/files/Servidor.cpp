#include "Servidor.h"

Servidor::Servidor(){
  std::cout<<"Escriba el núemro del puerto: ";
  std::cin>>puerto;
  buffer[0] = 0;
  tamBuffer = std::end(buffer)-std::begin(buffer);
  sizeOfBuffer = sizeof(buffer);
}

void Servidor::inicia(){
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  int valorLanzaError = lanzaError("\nError estableciendo la conexión.", "\nConexión del servidor establecida.", serverSocket);

  if(valorLanzaError < 0){
    desconecta();
    exit(1);
  }
  
  setDireccion();
  vincula();
  escucha();
  desconecta();
}

void Servidor::setDireccion(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void Servidor::vincula(){
  conexion = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  int valorLanzaError = lanzaError("Error al vincular el socket.", "Vinculación del servidor establecida.", conexion);

  if(valorLanzaError < 0){
    desconecta();
    exit(1);
  }
}

void Servidor::escucha(){
  listen(serverSocket, 10);
  aceptaClientes();
}

void Servidor::aceptaClientes(){
  sockaddr_in clientAddr;
  socklen_t clientAddrLen= sizeof(clientAddr);
  int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

  int valorLanzaError = lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket);

  if(valorLanzaError < 0){
    desconecta();
    exit(1);
  }
  manejaCliente(clientSocket, true);
}

void Servidor::manejaCliente(int clientSocket, bool hayConexion){
  while(hayConexion){
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::string st = std::string(buffer).substr(0,100);
      if(st == "EXIT"){
	std::cout<<"Adios cliente :)"<<std::endl;
	hayConexion = false;
      }
      std::cout<<buffer<<std::endl;
      buffer[0] = 0;

  }
}

void Servidor::desconecta(){
  close(serverSocket);
}

int Servidor::lanzaError(std::string mensaje1, std::string mensaje2, int valor){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    return -1;
  }
  
  std::cout<<mensaje2<<std::endl;
  return 0;
}
