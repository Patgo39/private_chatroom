#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message{
  enum class Type{
    RESPONSE,
    ADVICE,
    USERMESSAGE
  };
  enum class Visibility{
    PUBLIC,
    PRIVATE,
    ROOM
  };
  
  std::string text;
  std::string userName;
  std::string roomName;
  Type messageType;
  Visibility messageVisibility;

 public:
  Message();
  // Setters
  void setResponse(std::string text);
  void setRoomAdvice(std::string text, std::string roomName, std::string userName);
  void setServerAdvice(std::string text);
  void setPublicMessage(std::string text, std::string userName);
  void setRoomMessage(std::string text, std::string userName, std::string roomName);
  void setPrivateMessage(std::string text, std::string userName);

  // Getters
  Type getMessageType();
  Visibility getMessageVisibility();
  std::string getUserName();
  std::string getRoomName();
  std::string getText();
  
};
#endif
