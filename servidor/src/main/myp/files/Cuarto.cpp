#include "Cuarto.h"

Cuarto::Cuarto(std::string _nombreCuarto){
  nombreCuarto = _nombreCuarto;
}

std::string Cuarto::getNombre(){
  return nombreCuarto;
}

std::vector<int> Cuarto::getListaUsuarios(){
  std::vector<int> usuarios;

  for(auto elem:listaUsuarios){
    if(elem.second){
      usuarios.push_back(elem.first);
    }
  }
  return usuarios;
}

bool Cuarto::existeUsuario(int clientSocket){
  return listaUsuarios.find(clientSocket) != listaUsuarios.end();
}

void Cuarto::registraUsuario(int clientSocket){
  if(!existeUsuario(clientSocket)){
    listaUsuarios[clientSocket] = false;
  }
}

void Cuarto::activaUsuario(int clientSocket){
  if(!existeUsuario(clientSocket)){
    listaUsuarios[clientSocket] = true;
  }
}
