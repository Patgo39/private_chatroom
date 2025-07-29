#include "message.h"

Message::Message(){
  keepConection = true;
  roomOperation = Message::RoomOperation::NONE;
}

void Message::setServerResponse(std::string text, bool keepConnection) {
    // implementación aquí
}

void Message::setRoomAdvice(std::string text, std::string roomName, std::string userName) {
    // implementación aquí
}

void Message::setServerAdvice(std::string text) {
    // implementación aquí
}

void Message::setPublicMessage(std::string text, std::string userName) {
    // implementación aquí
}

void Message::setRoomMessage(std::string text, std::string userName, std::string roomName) {
    // implementación aquí
}

void Message::setPrivateMessage(std::string text, std::string userName) {
    // implementación aquí
}

// Getters

Message::Type Message::getMessageType() {
    // implementación aquí
}

Message::Visibility Message::getMessageVisibility() {
    // implementación aquí
}

std::string Message::getUserName() {
    // implementación aquí
}

std::string Message::getRoomName() {
    // implementación aquí
}

std::string Message::getText() {
    // implementación aquí
}
