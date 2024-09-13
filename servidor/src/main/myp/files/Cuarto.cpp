#include "Cuarto.h"

Cuarto::Cuarto(std::string _nombreCuarto){
  nombreCuarto = _nombreCuarto;
}

std::string Cuarto::getNombre(){
  return nombreCuarto;
}

std::vector<int> Cuarto::getVectorUsuarios(){
  std::vector<int> usuarios;

  for(auto elem:mapaUsuarios){
    if(elem.second){
      usuarios.push_back(elem.first);
    }
  }
  return usuarios;
}

bool Cuarto::existeUsuario(int clientSocket){
  return mapaUsuarios.find(clientSocket) != mapaUsuarios.end();
}

void Cuarto::registraUsuario(int clientSocket){
  if(!existeUsuario(clientSocket)){
    mapaUsuarios[clientSocket] = false;
  }
}

void Cuarto::activaUsuario(int clientSocket){
  if(!existeUsuario(clientSocket)){
    mapaUsuarios[clientSocket] = true;
  }
}

bool Cuarto::hayUsuarioUnido(int clientSocket){
  if(!existeUsuario(clientSocket))
    return false;
  return mapaUsuarios[clientSocket];
}

void Cuarto::borra(int clientSocket){
  mapaUsuarios.erase(clientSocket);
}
