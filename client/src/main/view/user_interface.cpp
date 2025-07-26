#include "user_interface.h"

UserInterface::UserInterface(){
  chat_options.push_back("General");
  selected_chat = 0;
  room_messages.insert({"General", {}});
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
}

void UserInterface::pushServerReply(std::string message){
  room_messages[chat_options[selected_chat]].push_back(message);

  while(room_messages[chat_options[selected_chat]].size() > 70){
    room_messages[chat_options[selected_chat]].pop_front();
  }
}

void UserInterface::eraseRoom(std::string roomName){
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

  // Se construye la pantalla de mensajes.
  auto message_display = Renderer([&] {
    std::vector<Element> lines;
    const std::string& current_room = chat_options[selected_chat];
    for (const auto& msg : room_messages[current_room]) {
      lines.push_back(paragraph(msg));
    }
    return vbox(std::move(lines));
  });


  // Se construye la interfaz.
  auto right_split = ResizableSplitBottom(right_bottom, message_display, &bottom_size);
  // Split izquierdo vs derecho
  auto root = ResizableSplitLeft(left_menu, right_split, &left_size);
  auto renderer = Renderer(root, [&] {return root->Render() | border;});

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);
}
