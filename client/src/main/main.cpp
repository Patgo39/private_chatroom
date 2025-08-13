#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <csignal>
#include <termios.h>
#include "client.h"
#include "command_manager.h"
#include "./view/user_interface.h"
#include "server_response_manager.h"
#include "message.h"
#include "command_result.h"

std::atomic<bool> continue_thread{true};

void manageReceivedMessages(UserInterface &tui, Client &c){
  ServerResponseManager serverManager = ServerResponseManager();
  while(continue_thread){
    
    std::string text = c.receiveMessages();
    if(text.empty()){
      continue;
    }
    
    try{
      Message msg = serverManager.getMessageFromResponse(text);
      tui.manageMessageResult(msg);
      continue_thread = msg.isConnectionKept();
    }catch(ServerResponseException& e){
      tui.pushMessageInCurrentRoom(e.what());
      continue_thread = false;
    }
  }
}

void manageCommand(Client &c, UserInterface &tui, UserInput input){
  if(!continue_thread)
      return;
  
  CommandManager cm = CommandManager();
  try{
    CommandResult cmdRes = cm.getJsonFromCommand(input);
    if(cmdRes.ownMessage)
      tui.pushMessageInCurrentRoom(cmdRes.output);
    else
      c.sendMessage(cmdRes.output);

    if(cmdRes.leaveRoom){
      tui.eraseRoom(cmdRes.roomToLeave);
    }
    
    if(!cmdRes.stillConnected){
      continue_thread = false;
      c.closeConnection();
    }
  }catch(CommandException &e){
    std::string error = e.what();
    tui.pushMessageInCurrentRoom(error);
  }
}

int main(){
  
  const int maxSizeBuffer = 1024;
  UserInterface tui = UserInterface(maxSizeBuffer);
  int port;
  try{
    port = std::stoi(tui.askAndGetPort());
  }catch(const std::invalid_argument& e){
    std::cout<<"INVALID input type.";
    exit(1);
  }
  std::string ip = tui.askAndGetIp();

  // Ignora la señal CTRL + C
  std::signal(SIGINT, SIG_IGN);
  // Ignora la señal CTRL + Z
  std::signal(SIGTSTP, SIG_IGN);
  
  Client c = Client(port, maxSizeBuffer, ip);
  
  try{
    // Se inicia la conexión con el servidor.
    c.start();
    
  }catch(ClientConnectionException &e){
    std::string error = e.what();
    tui.showMessageOnTerminal(error);
    exit(1);
  }
  
  std::thread textual_user_interface(&UserInterface::startMainLoop, &tui);
  //Se escuchan e imprimen los mensajes recibidos.
  std::thread thread_show_messages(manageReceivedMessages, std::ref(tui), std::ref(c));

  // Ciclo que mantiene la conexión con el servidor
  while(continue_thread){
    
    //Se obtienen los mensajes del ususario.
    UserInput input = tui.getUserInput();
    manageCommand(c, tui, input);
  }
  
  tui.endMainLoop();
  textual_user_interface.join();
  thread_show_messages.join();
  tui.showMessageOnTerminal("You are now disconnected.");
  
  return 0;
  
}
