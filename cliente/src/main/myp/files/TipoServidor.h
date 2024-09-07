/* La enumeración TipoServidor contempla todas las respuestas a las peticiones
 * de los usuarios.
 */
#ifndef TIPOSERVIDOR_H
#define TIPOSERVIDOR_H

#include <iostream>
#include <string>

class TipoServidor{
 public:
  enum Tipo{
  //El cliente recibe una respuesta del servidor.
  RESPONSE = 1,
  //Un nuevo usuario se conectó.
  NEW_USER = 2,
  //Notifica a los clientes que un usuario cambió su estado.
  NEW_STATUS = 3,
    //Indica que se mandará la lista de ususarios.
  USER_LIST = 4,
  //Notifica al cliente que recibe un mensaje privado.
  TEXT_FROM = 5,
  //Notifica al cliente que un usuario mandó un texto público.
  PUBLIC_TEXT_FROM = 6,
  //Indica a los usuarios de la sala que un nuevo usuario se unió.
  JOINED_ROOM = 7,
  //Envía al usuario la lista de ususarios de la sala.
  ROOM_USER_LIST = 8,
  //El usuario recibe un dexto en un cuarto.
  ROOM_TEXT_FROM = 9,
  //Indica a los ususarios de la sala que otro usuario se fue.
  LEFT_ROOM = 10,
  //Indica a los usuarios que alguien se desconectó.
  DISCONNECTED = 11
  };
  static std::string getString(TipoServidor::Tipo);
};

#endif
