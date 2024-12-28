#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "./view/screen.h"
#include "client.h"

std::atomic<bool> continue_thread{true};

void manageReceivedMessages(Screen sc, Client c){
  
  while(continue_thread){
    
    int received = 0;
    std::string text = c.receiveMessages(received);
    
    if(received <= 0)
      continue;
    
    sc.showMessage("Client", text.c_str(), true, false, true);
  }
}

int main(){
  const int maxSizeBuffer = 1024;
  Screen sc = Screen(maxSizeBuffer);

  int port = std::stoi(sc.askAndGetPort());
  std::string ip = sc.askAndGetIp();
  Client c = Client(port, maxSizeBuffer, ip);
  
  try{
    // Se inicia la conexión con el servidor.
    c.start();
    //Se escuchan e imprimen los mensajes recibidos.
    std::thread thread_show_messages(manageReceivedMessages, sc, c);

    while(continue_thread){
      
      //Se obtienen los mensajes del ususario.
      std::string userMessage = sc.getMessage();
      //Si el texto ingresado es x, termina la conexión.
      if(userMessage == "x;"){
	std::cout<<"byeee"<<std::endl;
	continue_thread = false;
      }else{
	c.sendMessage(userMessage);
      }
    }
    
    thread_show_messages.join();
    
  }catch(ClientConnectionException &e){
    std::string error = e.what();
    sc.showMessage("server", error, true, true, false);
  }
  
  return 0;
  
}

