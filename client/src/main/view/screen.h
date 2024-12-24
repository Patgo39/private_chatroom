/**
 * Clase Screen funciona como la vista textual del chatroom.
 *
 * Se monstraran todos los mensjaes ya sean respuesta del servidor, mensajes
 * del chat general, mensajes privados y los mensajes de cuartos.
 * Además se recibirá la entrada del usuario al momento de escribir un mensaje
 * o escribir un comando.
 */
#ifndef SCREEN_h
#define SCREEN_h

#include <iostream>
#include <string>

class Screen{
  //Cadena para que el usuario sepa dónde escribir su comando o mensaje.
  std::string youString;
  //Tamaño del buffer de entrada.
  int bufferSize;
  
  
 public:
  //Constructor
  Screen(int _bufferSize);
  //Se pregunta y se recibe la entrada del usuario para el puerto.
  std::string askAndGetPort();
  //Se pregunta y se recibe la entrada del usuario para la ip.
  std::string askAndGetIp();
  //Se muestra un mensaje de otro usuario o la respuesta del servidor.
  void showMessage(std::string name, const char buffer[], bool general, bool serverResponse, bool continueConnected);
  //Se obtiene la entrada del usuario.
  std::string getMessage();
};


#endif
