#include "user_interface.h"

UserInterface::UserInterface(int _bufferSize){
  bufferSize = _bufferSize;
  chat_options.push_back("General");
  selected_chat = 0;
  room_messages.insert({"General", {}});
}

std::string UserInterface::askAndGetPort(){
  std::string port;
  std::cout<<"Type the port: ";
  std::cin>>port;
  return port;
}

std::string UserInterface::askAndGetIp(){
  std::string ip;
  std::cout<<"Type the ip: ";
  std::cin>>ip;
  return ip;
}

void UserInterface::manageMessageResult(Message msg){
  Type messageType = msg.getMessageType();

  switch(messageType){
    //Caso en el que se crea un nuevo cuarto y se le informa al usuario.
  case Type::ACTION_WITH_TEXT:
    {
      Action act = msg.getMessageOperationType();
      switch(act){
      case Action::CREATE:
	{
	  std::string message = msg.getText();
	  std::string room = msg.getRoomName();
	  addNewRoom(room);
	  pushMessageInCurrentRoom(message);
	  break;
	}
      case Action::LEAVE: break;
	break;
      }
      break;
    }
    // Caso de mensajes generales, privados y de cuarto.
  case Type::TEXT:
    {
      Text text = msg.getMessageTextType();
      std::string username = msg.getUserName();
      std::string txt = msg.getText();
      std::string updated_message = "\n'" + username + "': " + txt;
      switch(text){
      case Text::PUBLIC:
	pushRoomMessage("General", updated_message);
	break;
	
      case Text::PRIVATE:
	{
	  std::string update_message = "PRIVATE->" + updated_message;
	  pushRoomMessage("General", updated_message);
	  break;
	}
      case Text::ROOM:
	{
	  std::string roomName = msg.getRoomName();
	  pushRoomMessage(roomName, updated_message);
	  break;
	}
      }
      
      break;
    }
    // Informar al usuario de acciones de otros usuarios.
  case Type::ADVICE:
    {
      Advice adv = msg.getMessageAdviceType();
      std::string txt = msg.getText();
      switch(adv){
      case Advice::RESPONSE:
	{
	  std::string updated_txt = "SERVER_RESPONSE: "+ txt;
	  pushMessageInCurrentRoom(updated_txt);
	  break;
	}
      case Advice::NORMAL_ADVICE:
	{
	  pushMessageToAllRooms(txt);
	  break;
	}
      case Advice::ROOM_ADVICE:
	{
	  std::string roomName = msg.getRoomName();
	  pushRoomMessage(roomName, txt);
	  break;
	}
      }
      break;
    }
  }
}

void UserInterface::showMessageOnTerminal(std::string message){
  std::cout<<message<<std::endl;
}

void UserInterface::addNewRoom(std::string roomName){
  room_messages.insert({roomName, {}}); // Se agrega el cuarto en el mapa.
  chat_options.push_back(roomName); // Se agrega el cuarto en el vector.
}

void UserInterface::pushRoomMessage(std::string chatName, std::string message){
  
  room_messages[chatName].push_back(message);

  while(room_messages[chatName].size() > 70){
    room_messages[chatName].pop_front();
  }
  screen.PostEvent(Event::Custom);
}

void UserInterface::pushMessageInCurrentRoom(std::string message){
  room_messages[chat_options[selected_chat]].push_back(message);

  while(room_messages[chat_options[selected_chat]].size() > 70){
    room_messages[chat_options[selected_chat]].pop_front();
  }
  screen.PostEvent(Event::Custom);
}

void UserInterface::eraseRoom(std::string roomName){
  if(room_messages.find(roomName) == room_messages.end())
    return;
      
  room_messages.erase(roomName);

  int i = 0;
  for(std::string chat_name : chat_options){
    if(chat_name == roomName){
      break;
    }
    i++;
  }

  chat_options.erase(chat_options.begin() + i);
}

void UserInterface::pushMessageToAllRooms(std::string message){
  for(auto& pair : room_messages){
    pair.second.push_back(message);
  }
  screen.PostEvent(Event::Custom);
}

std::string UserInterface::getUserMessage(){
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] {return !user_input.empty();});
  
  std::string msg = user_input;
  user_input.clear();
  return msg;
}

void UserInterface::onUserInputEvent(std::string input){
  std::lock_guard<std::mutex> lock(mtx);
  user_input = input;
  cv.notify_one();
}

void UserInterface::startMainLoop(){
  exit_loop = screen.ExitLoopClosure();
  
  // Se construye la lista de chats.
  Component chat_menu = Menu(&chat_options, &selected_chat);

  auto left_menu = Renderer(chat_menu, [&] {
    return vbox({
	text("Chat list") | center | border,
	chat_menu->Render() | border
      });
  });

  // Se construye la entrada del usuario
  std::string user_input_aux;
  Component input_user_component = Input(&user_input_aux, "Type your message...");
  
  int left_size = 20;
  int bottom_size = 4;
  
  auto input_catch = CatchEvent(input_user_component, [&] (Event event) {
    if(event == Event::Return){ // Enter
      if(!user_input_aux.empty()){
	room_messages[chat_options[selected_chat]].push_back(user_input_aux);
	onUserInputEvent(user_input_aux);
	user_input_aux.clear();
	return true;
      }
    }
    return false;
  });

  auto right_bottom = Renderer(input_catch, [&] {
    return vbox({
	text("Message Input") | center,
	input_catch->Render() | border
      });
  });

  // Barra scroll.
  float scroll_y = 0.1;
  SliderOption<float> option_y;
  option_y.value = &scroll_y;
  option_y.min = 0.f;
  option_y.max = 1.f;
  option_y.increment = 0.1f;
  option_y.direction = Direction::Down;
  option_y.color_active = Color::Yellow;
  option_y.color_inactive = Color::YellowLight;
  auto scrollbar_y = Slider(option_y);
  
  // Se construye la pantalla de mensajes.
  auto content_messages = Renderer([&] {
    std::vector<Element> lines;
    const std::string& current_room = chat_options[selected_chat];
    for (const auto& msg : room_messages[current_room]) {
      lines.push_back(paragraph(msg));
    }
    return vbox(std::move(lines));
  });


  // Se construye la interfaz.
  auto right_split = ResizableSplitBottom(right_bottom, content_messages, &bottom_size);
  // Split izquierdo vs derecho
  auto root = ResizableSplitLeft(left_menu, right_split, &left_size);
  auto renderer = Renderer(root, [&] {return root->Render() | border;});

  screen.Loop(renderer);
}

void UserInterface::endMainLoop(){
  if(exit_loop) {
    exit_loop();         
    std::cout.flush();           
  }
}
