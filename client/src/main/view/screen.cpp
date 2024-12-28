
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

/**
 * Se muestra un mensaje en el terminal. El formato dependerá de los parámetros
 * específicados.
 * @param name el nombre del usuario que envió el mensaje.
 * @param buffer el buffer con el texto a imprimir.
 * @param general true si el mensaje no es del servidor y es un mensaje privado.
 * @param true si el mensaje es una respuesta del servidor.
 */
void Screen::showMessage(std::string name, std::string buffer, bool general, bool serverResponse, bool continueConnected){
  
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
  if(continueConnected){
    std::cout<<youString;
    std::fflush(stdout);
  }
}

std::string Screen::getMessage(){
  
  char buffer[bufferSize];
  std::cout<<youString;
  std::cin>>std::ws; // Descarta espacios en blanco de la entrada.
  std::cin.getline(buffer, bufferSize, '\n');
  std::fflush(stdout);
  return buffer;
}
