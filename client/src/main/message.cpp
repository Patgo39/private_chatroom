#include "message.h"

Message::Message(){
  keepConection = true;
}

void Message::setRoomCreationWithAdvice(std::string _roomName, std::string _text){
  type = Type::ACTION_WITH_TEXT;
  subtype = Action::CREATE;
  roomName = _roomName;
  text = _text;
}

void Message::setServerResponse(std::string _text, bool _keepConection) {
  type = Type::ADVICE;
  subtype = Advice::RESPONSE;
  keepConection = _keepConection;
  text = _text;
}

void Message::setRoomAdvice(std::string _text, std::string _roomName) {
  type = Type::ADVICE;
  subtype = Advice::ROOM_ADVICE;
  text = _text;
  roomName = _roomName;
}

void Message::setServerAdvice(std::string _text) {
  type = Type::ADVICE;
  subtype = Advice::NORMAL_ADVICE;
  text = _text;
}

void Message::setPublicMessage(std::string _text, std::string _userName) {
  type = Type::TEXT;
  subtype = Text::PUBLIC;
  text = _text;
  userName = _userName;
}

void Message::setRoomMessage(std::string _text, std::string _roomName, std::string _userName){
  type = Type::TEXT;
  subtype = Text::ROOM;
  text = _text;
  roomName = _roomName;
  userName = _userName;
}

void Message::setPrivateMessage(std::string _text, std::string _userName) {
  type = Type::TEXT;
  subtype = Text::PRIVATE;
  text = _text;
  userName = _userName;
}

// Getters

Type Message::getMessageType(){
  return type;
}

Advice Message::getMessageAdviceType(){
  if(!std::holds_alternative<Advice>(subtype)){
    throw std::logic_error("Not an Advice message.");
  }

  return std::get<Advice>(subtype);
}

Text Message::getMessageTextType(){
  if(!std::holds_alternative<Text>(subtype)){
    throw std::logic_error("Not a Text message.");
  }

  return std::get<Text>(subtype);
}

Action Message::getMessageOperationType(){
  if(!std::holds_alternative<Action>(subtype)){
    throw std::logic_error("Not an Operation message.");
  }

  return std::get<Action>(subtype);
}

std::string Message::getUserName() {
  return userName;
}

std::string Message::getRoomName() {
  return roomName;
}

std::string Message::getText() {
  return text;
}
