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

void Client::setUserStatus(UserStatus::Status _status){
  status = _status;
}

std::string Client::getUserName(){
  return userName;
}

std::string Client::getUserStatus(){
  return UserStatus::getString(status);
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

void Client::joinToRoom(std::string roomName){
  rooms.push_back(roomName);
}

void Client::forgetRoom(std::string roomName){
  int position = 0;
  for(std::string name:rooms){
    if(name == roomName){
      rooms.erase(rooms.begin() + position);
      break;
    }
    position ++;
  }
  
}

std::vector<std::string> Client::getRoomVector(){
  return rooms;
}


