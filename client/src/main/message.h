#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message{
public:
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

  enum class RoomOperation{
    CREATE,
    LEAVE,
    NONE
  };
private:
  std::string text;
  std::string userName;
  std::string roomName;
  bool keepConection;
  Type messageType;
  Visibility messageVisibility;
  RoomOperation roomOperation;

 public:
  Message();
  // Setters
  void setRoomCreation(std::string roomName);
  void setRoomElimination(std::string roomName);
  void setServerResponse(std::string text,  bool keepConection);
  void setRoomAdvice(std::string text, std::string roomName, std::string userName);
  void setServerAdvice(std::string text);
  void setPublicMessage(std::string text, std::string userName);
  void setRoomMessage(std::string text, std::string userName, std::string roomName);
  void setPrivateMessage(std::string text, std::string userName);

  // Getters
  Type getMessageType();
  Visibility getMessageVisibility();
  RoomOperation getRoomOperation();
  std::string getUserName();
  std::string getRoomName();
  std::string getText();
  
};
#endif
