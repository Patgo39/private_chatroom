#include "Servidor.h"

Servidor::Servidor(){
  std::cout<<"Escriba el número del puerto: ";
  std::cin>>puerto;
}

void Servidor::inicia(){
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  lanzaError("\nError estableciendo la conexión.", "\nConexión del servidor establecida.", serverSocket, true);
  
  vincula();
  conectaClientes();
  desconecta();
}

void Servidor::vincula(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  
  conexion = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  lanzaError("Error al vincular el socket.", "Vinculación del servidor establecida.", conexion, true);
}

void Servidor::conectaClientes(){
  listen(serverSocket, 10);
  
  int clientSocket;
  sockaddr_in clientAddr;
  socklen_t clientAddrLen;
  
  while(true){
    clientAddrLen= sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket, true);
      
    std::thread tclient(&Servidor::manejaCliente, this, clientSocket);
    tclient.detach();
  }

  desconecta();
}

void Servidor::manejaCliente(int clientSocket){
  char buffer[512];
  int cont = 0;
  Usuario us;
  
  while(recv(clientSocket, buffer, sizeof(buffer), 0) != 0){
    
    std::string st = std::string(buffer).substr(0, 512);

    if(cont == 0){
      us = Usuario(st, clientSocket);
      mapa[clientSocket] = us;
      std::cout<<"Long mapa: "<<mapa.size()<<std::endl;
      cont++;
    }

    mandaMensaje(us, buffer);
    
    if(st == "EXIT"){
      mtx.lock();
      std::cout<<"Adios cliente :)"<<std::endl;
      desconectaUsuario(us.getSocket());
      mtx.unlock();
    }
    buffer[0] = 0;
    
  }
}

void Servidor::desconectaUsuario(int socket){
  mapa.erase(socket);
  if(mapa.size() == 0){
    desconecta();
  }
}

void Servidor::desconecta(){
  close(serverSocket);
  std::cout<<"\nServidor desconectado"<<std::endl;
}

void Servidor::lanzaError(std::string mensaje1, std::string mensaje2, int valor, bool termina){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    if(termina){
      desconecta();
      exit(1);
    }
  }
  
  std::cout<<mensaje2<<std::endl;
}

void Servidor::mandaMensaje(Usuario us, char buffer[]){
  mtx.lock();
  
  std::string cadena = us.getNombre() + ": ";
  std::string st = std::string(buffer).substr(0, 512);

  cadena += st;
  
  std::cout<< cadena <<std::endl;
  for(auto elemento:mapa){
    if(elemento.first != us.getSocket()){
      send(elemento.first, cadena.c_str(), cadena.length(), 0);
    }
  }
  mtx.unlock();
}
