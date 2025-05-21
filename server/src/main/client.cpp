#include <client.h>

Client::Client(int _clientSocket){
  clientSocket = _clientSocket;
  identified = false;
  userName = "";
  status = UserStatus::Status::ACTIVE;
}

void Client::setUserName(std::string _userName){
  if(userName == ""){
    userName = _userName;
  }
}

std::string Client::getUserName(){
  return userName;
}

void Client::identify(){
  identified = true;
}


int Client::getSocket(){
  return clientSocket;
}


bool Client::isIdentified(){
  return identified;
}


