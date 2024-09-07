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
    
    char buff[512] = {};
    std::string nombre;
    bool valido = true;
    recv(clientSocket, buff, sizeof(buff), 0);
    std::string respuesta = manejaPeticion(buff, valido, nombre);
    
    send(clientSocket, respuesta.c_str(), respuesta.length(), 0);
    if(!valido) continue;
    
    lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket, true);

      Usuario us(nombre, clientSocket);
      mapa[clientSocket] = us;
   
      
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

    mandaMensaje(us, buffer);
    
    if(st == "EXIT"){
      mtx.lock();
      desconectaUsuario(us.getSocket());
      mtx.unlock();
    }
    buffer[0] = 0;
    
  }
}

void Servidor::desconectaUsuario(int socket){
  Usuario us = mapa[socket];
  mapa.erase(socket);
  std::cout<<us.getNombre()<<" se desconectó."<<std::endl;
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
  
  
  for(auto& elemento:mapa){
    if(elemento.first != us.getSocket()){
      std::cout<< cadena.c_str() <<std::endl;
      send(elemento.first, cadena.c_str(), cadena.length(), 0);
    }
  }
  mtx.unlock();
}

std::string Servidor::manejaPeticion(char buffer[], bool &valido, std::string &nombre){
  int tipoCliente = ManejaPeticionCliente::manejaPeticion(buffer);
  std::string respuesta;
  
  switch(tipoCliente){
  case TipoCliente::Tipo::IDENTIFY:
    return ManejaPeticionCliente::manejaIdentificacion(buffer, mapa, valido, nombre);
  case TipoCliente::Tipo::STATUS:
  case TipoCliente::Tipo::USERS:
  case TipoCliente::Tipo::TEXT:
  case TipoCliente::Tipo::PUBLIC_TEXT:
  case TipoCliente::Tipo::NEW_ROOM:
  case TipoCliente::Tipo::INVITE:
  case TipoCliente::Tipo::JOIN_ROOM:
  case TipoCliente::Tipo::ROOM_USERS:
  case TipoCliente::Tipo::ROOM_TEXT:
  case TipoCliente::Tipo::LEAVE_ROOM:
  case TipoCliente::Tipo::DISCONNECT:
    break;
  }
}
