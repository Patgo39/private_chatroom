
#include "screen.h"


Screen::Screen(int _bufferSize){
  youString = "You: ";
  bufferSize = _bufferSize;
}

std::string Screen::askAndGetPort(){
  std::string port;
  std::cout<<"Type the port: ";
  std::cin>>port;
  return port;
}

std::string Screen::askAndGetIp(){
  std::string ip;
  std::cout<<"Type the ip adress: ";
  std::cin>>ip;
  return ip;
}


void Screen::showMessage(std::string name, char buffer[], bool general, bool serverResponse){
  std::cout<<"\r"<<std::string(50, ' ')<<"\r";
  if(serverResponse){
    std::cout<<buffer<<std::endl;
  }else{
    std::string message = name + ": " + buffer;
    if(general){
      std::cout<<message<<std::endl;
    }else{
      std::cout<<message<<std::endl;
    }
  }

  std::cout<<youString;
  std::fflush(stdout);
}

std::string Screen::getMessage(){
  
  char buffer[bufferSize];
  std::cin.ignore(100, '\n');
  std::cout<<youString;
  std::cin.getline(buffer, bufferSize, '\n');
  return buffer;
}
