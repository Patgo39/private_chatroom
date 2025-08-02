#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <memory>
#include <string>
#include <list>
#include <map>
#include <mutex>
#include <condition_variable>
#include <csignal>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <ftxui/component/captured_mouse.hpp>
#include "ftxui/dom/elements.hpp"
#include "scroller.h"
#include "../message.h"
#include "../user_input.h"

using namespace ftxui;

class UserInterface{
  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  std::function<void()> exit_loop;
  
  int bufferSize;
  int selected_chat;
  std::string user_input;
  std::vector<std::string> chat_options;
  std::map<std::string, std::list<std::string>> room_messages;
  std::mutex mtx;
  std::condition_variable cv;
public:
  UserInterface(int _bufferSize);
  std::string askAndGetPort();
  std::string askAndGetIp();
  void manageMessageResult(Message msg);
  void showMessageOnTerminal(std::string message);
  void pushMessageInCurrentRoom(std::string message);
  void eraseRoom(std::string roomName);
  std::string getUserMessage();
  void startMainLoop();
  void endMainLoop();

private:
  void addNewRoom(std::string roomName);
  void pushRoomMessage(std::string chatName, std::string message);
  void onUserInputEvent(std::string input);
  void pushMessageToAllRooms(std::string message);
};

#endif
