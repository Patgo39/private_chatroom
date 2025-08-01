#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include <variant>
#include <variant>

enum class Type{
  ACTION_WITH_TEXT,
  TEXT,
  ADVICE
};

enum class Advice{
  RESPONSE,
  NORMAL_ADVICE,
  ROOM_ADVICE
  };

// Valida unicamente cuando el tipo del mensaje es un mensaje de ususario.
enum class Text{
  PUBLIC,
  PRIVATE,
  ROOM
};

enum class Action{
  CREATE,
  LEAVE
};

class Message{
  
  std::string text;
  std::string userName;
  std::string roomName;
  bool keepConnection;
  Type type;
  std::variant<Action, Text, Advice> subtype;

 public:
  Message();
  // Setters
  void setRoomCreationWithAdvice(std::string _roomName, std::string text);
  
  void setServerResponse(std::string _text,  bool _keepConection);
  void setRoomAdvice(std::string _text, std::string _roomName);
  void setServerAdvice(std::string _text);
  
  void setPublicMessage(std::string _text, std::string _userName);
  void setRoomMessage(std::string _text, std::string _userName, std::string _roomName);
  void setPrivateMessage(std::string _text, std::string _userName);

  // Getters
  Type getMessageType();
  Advice getMessageAdviceType();
  Text getMessageTextType();
  Action getMessageOperationType();
  std::string getUserName();
  std::string getRoomName();
  std::string getText();
  bool isConnectionKept();
};
#endif
