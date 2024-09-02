#include "Servidor.h"

Servidor::Servidor(){
  std::cout<<"Escriba el núemro del puerto: ";
  std::cin>>puerto;
  buffer[0] = 0;
  tamBuffer = std::end(buffer)-std::begin(buffer);
  sizeOfBuffer = sizeof(buffer);
  aceptaConexiones = true;
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
  std::thread tAcepta(&Servidor::aceptaClientes, this);
  tAcepta.join();
}

void Servidor::aceptaClientes(){
  while(aceptaConexiones){
    sockaddr_in clientAddr;
    socklen_t clientAddrLen= sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    int valorLanzaError = lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket);
    
    if(valorLanzaError < 0){
      desconecta();
      exit(1);
    }
    std::thread tclient(&Servidor::manejaCliente, this, clientSocket, true);
    tclient.detach();
  }
}

void Servidor::manejaCliente(int clientSocket, bool hayConexion){
  Usuario us;
  int cont = 0;
  do{
    mtx.lock();
    recv(clientSocket, buffer, sizeof(buffer), 0);
    if(cont == 0){
      mtx.lock();
      std::string s = std::string(buffer).substr(0,100);
      us = Usuario(s, clientSocket);
      lista.push_back(us);
      std::cout<<"Bienvenido "<<s<<std::endl;
      cont++;
      
    }else{
      std::string st = std::string(buffer).substr(0,100);
      if(st == "EXIT"){
	std::cout<<"Adios cliente :)"<<std::endl;
	hayConexion = false;
	desconectaUsuario(us);
      }
      std::cout<<us.getNombre()<<": "<<buffer<<std::endl;
      buffer[0] = 0;
    }
    mtx.unlock();
  }while(hayConexion);
}

void Servidor::desconectaUsuario(Usuario us){
  int pos = getUsuario(us.getNombre());
  
  lista.erase(lista.begin() + pos);
  if(lista.size() == 0){
    aceptaConexiones = false;
  }
}

void Servidor::desconecta(){
  close(serverSocket);
  std::cout<<"\nServidor desconectado"<<std::endl;
}

int Servidor::lanzaError(std::string mensaje1, std::string mensaje2, int valor){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    return -1;
  }
  
  std::cout<<mensaje2<<std::endl;
  return 0;
}

int Servidor::getUsuario(std::string nombre){
  int cont = 0;
  for(Usuario us: lista){
    if(us.getNombre() == nombre){
      return cont;
    }
    cont++;
  }
  return -1;
}
