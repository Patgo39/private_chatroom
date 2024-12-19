#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "./view/screen.h"
#include "client.h"

std::atomic<bool> continue_thread{true};

void manageReceivedMessages(Screen sc){
  while(continue_thread){
    
  }
}

int main(){
  const int maxSizeBuffer = 1024;
  Screen sc = Screen(maxSizeBuffer);

  int port = std::stoi(sc.askAndGetPort());
  std::string ip = sc.askAndGetIp();

  // Se inicia la conexión con el servidor.
  Client c = Client(port, maxSizeBuffer, ip);

  try{
    c.start();

    std::thread thread_show_messages(manageReceivedMessages, sc);

    while(continue_thread){
      std::string userMessage = sc.getMessage();
      if(userMessage == "x;"){
	std::cout<<"byeee"<<std::endl;
	continue_thread = false;
      }
    }
    thread_show_messages.join();
  }catch(ClientConnectionException &e){
    char text[maxSizeBuffer];
    strncpy(text, e.what(), maxSizeBuffer);
    sc.showMessage("server", text, true, true, false);
  }
  
  return 0;
  
}

