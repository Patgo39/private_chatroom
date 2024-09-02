#include "Cliente.h"

Cliente::Cliente(){
  std::cout<<"Escriba el núemro del puerto: ";
  std::cin>>puerto;
  buffer[0] = 0;
  tamBuffer = std::end(buffer)-std::begin(buffer);
  sizeOfBuffer = sizeof(buffer);
}

void Cliente::inicia(){
  //Se crea el socket.
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  int  valorLanzaError = lanzaError("\nError estableciendo la conexión.", "\nConexión del cliente establecida.", clientSocket);
  
  if(valorLanzaError < 0){
    desconecta();
    exit(1);
  } 

  setDireccion();
  conecta();
  desconecta();
}

void Cliente::setDireccion(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void Cliente::conecta(){
  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  int err = lanzaError("No se pudo conectar al servidor.", "Conexión con el servidor establecida.", conexion);

  if(err < 0){
    desconecta();
    exit(1);
  }

  mantenerConexion = true;

  comunicar();
}

void Cliente::comunicar(){
  int cont = 0;
  while(mantenerConexion){
    if(cont == 0){
      std::cout<<"Introduzca su nombre: ";
      std::cin >> std::ws;
      std::cin.getline(buffer, 512, '\n');
    }else{
      std::cout<<"Mensaje: ";
      std::cin.getline(buffer, 512, '\n');
    }

    send(clientSocket, &buffer, sizeOfBuffer, 0);
    std::string st = std::string(buffer).substr(0, tamBuffer);
    if(st == "EXIT")
      mantenerConexion = false;

    if(cont < 1) cont++;
  }
}

void Cliente::desconecta(){
  close(clientSocket);
}

int Cliente::lanzaError(std::string mensaje1, std::string mensaje2, int valor){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    return -1;
  }
  
  std::cout<<mensaje2<<std::endl;
  return 0;
}
