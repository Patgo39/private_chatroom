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
    
    if(!identificarUsuario(clientSocket)) continue;
      
    std::thread tclient(&Servidor::manejaCliente, this, clientSocket);
    tclient.detach();
  }

  desconecta();
}

void Servidor::manejaCliente(int clientSocket){
  std::string buffer;
  Usuario us = mapa[clientSocket];
  
  while(true){
    
    buffer = recibeMensaje(clientSocket);

    mandaMensajeGeneral(us, buffer);
    
    if(buffer == "EXIT"){
      mtx.lock();
      desconectaUsuario(us.getSocket());
      mtx.unlock();
    }
    buffer.clear();
    
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

void Servidor::mandaMensajeGeneral(Usuario us, std::string cadena){
  mtx.lock();
  
  for(auto& elemento:mapa){
    if(elemento.first != us.getSocket()){
      send(elemento.first, cadena.c_str(), cadena.length(), 0);
    }
  }
  mtx.unlock();
}

void Servidor::mandaMensajeIndividual(int clientSocket, std::string buffer){
  send(clientSocket, buffer.c_str(), buffer.length(), 0);
}

std::string Servidor::manejaPeticion(std::string buffer, bool &valido){
  int tipoCliente = ManejaPeticionCliente::manejaPeticion(buffer);
  std::string respuesta;
  
  switch(tipoCliente){
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

bool Servidor::identificarUsuario(int clientSocket){
  std::string buff;
  std::string nombre;
  bool valido = true;
  
  buff = recibeMensaje(clientSocket);
    
  std::string respuesta = ManejaPeticionCliente::manejaIdentificacion(buff, mapa, valido, nombre);
  
  mandaMensajeIndividual(clientSocket, respuesta);
    if(!valido) return false;
    
    
    lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket, true);
    
    mtx.lock();
    Usuario us(nombre, clientSocket);
    mapa[clientSocket] = us;
    mtx.unlock();
    
    return true;
}

std::string Servidor::recibeMensaje(int clientSocket){
  char buffer[512] = {};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  return std::string(buffer);
}
