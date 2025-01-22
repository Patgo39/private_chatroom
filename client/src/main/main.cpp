#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "./view/screen.h"
#include "client.h"
#include "command_manager.h"

std::atomic<bool> continue_thread{true};

void manageReceivedMessages(Screen &sc, Client &c){
  
  while(continue_thread){
    
    int received = -1;
    std::string text = c.receiveMessages(received);
    
    if(received <= 0)
      continue;

    sc.showMessage("Client", text.c_str(), true, false, true);
    }
}

void manageCommand(Client &c, Screen &sc, std::string command){
  bool stillConnected = true;
  CommandManager cm = CommandManager();
  try{
    std::string json = cm.getJsonFromCommand(command, stillConnected);
    c.sendMessage(json);

    if(!stillConnected){
      c.closeConection();
      continue_thread = false;
      sc.showMessage("Server", "You're now disconnected.", true, true, false);
    }
  }catch(CommandException &e){
    std::string error = e.what();
    sc.showMessage("Error", error, true, true, false);
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
    std::thread thread_show_messages(manageReceivedMessages, std::ref(sc), std::ref(c));
    thread_show_messages.detach();

    while(continue_thread){
      
      //Se obtienen los mensajes del ususario.
      std::string userMessage = sc.getMessage();

      manageCommand(c, sc, userMessage);
    }
    
    
  }catch(ClientConnectionException &e){
    std::string error = e.what();
    sc.showMessage("Server", error, true, true, false);
  }
  
  return 0;
  
}

