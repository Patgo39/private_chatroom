#include "Cliente.h"

Cliente::Cliente(){
  std::cout<<"Escriba el número del puerto: ";
  std::cin>>puerto;
  
  std::cout<<"\nEscriba su nombre: ";
  std::cin>>nombre;
  if(nombre.length() > 8){
    std::cout<<"El nombre no debe tener más de 8 caracteres."<<std::endl;
    exit(1);
  }
}

void Cliente::inicia(){
  //Se crea el socket.
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  lanzaError("\nError estableciendo la conexión.", "\nConexión del cliente establecida.", clientSocket, true);
  
  conecta();
  desconecta();
}


void Cliente::conecta(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  
  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  lanzaError("No se pudo conectar al servidor.", "Conexión con el servidor establecida.", conexion, true);
  
  send(clientSocket, nombre.c_str(), nombre.length() + 1, 0);
  
  std::thread t1(&Cliente::mandaMensaje, this);
  std::thread t2(&Cliente::recibeMensaje, this);

  t1.join();
  t2.join();

  desconecta();
}

void Cliente::mandaMensaje(){
  char buffer[512] = {};
  
  while(true){
    buffer[0] = 0;
    std::cout<<"Mensaje: ";
    std::cin>>std::ws;
    std::cin.getline(buffer, 512, '\n');

    send(clientSocket, &buffer, sizeof(buffer), 0);
    std::string st = std::string(buffer).substr(0, 512);
    if(st == "EXIT"){
      desconecta();
      exit(1);
    }
  }
}

void Cliente::recibeMensaje(){
  char buff[512] = {};
  while(true){
    recv(clientSocket, buff, sizeof(buff), 0);
    std::cout<<buff<<std::endl;
  }
}

void Cliente::desconecta(){
  close(clientSocket);
}

void Cliente::lanzaError(std::string mensaje1, std::string mensaje2, int valor, bool termina){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    if(termina){
      desconecta();
      exit(1);
    }
  }
  
  std::cout<<mensaje2<<std::endl;
}
