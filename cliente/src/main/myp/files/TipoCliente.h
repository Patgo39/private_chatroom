/* TipoCliente es una enumeración que contempla todas las solicitudes que un
 * usuario puede hacer al servidor.
 */
#ifndef TIPOCLIENTE_H
#define TIPOCLIENTE_H

#include <iostream>
#include <string>

class TipoCliente{
 public:
  enum Tipo{
    //Se identifica el usuario.
    IDENTIFY = 12,
    //Cambia el estatus del ususario.
    STATUS = 13,
    //Pide la lista de usuarios.
    USERS = 14,
    //Manda texto privado a un usuario,
    TEXT = 15,
    //Manda un mensaje publico.
    PUBLIC_TEXT = 16,
    //Crea una nueva sala.
    NEW_ROOM = 17,
    //Invita a uno o más usuarios a una sala.
    INVITE= 18,
  //El usuario se une a una sala.
    JOIN_ROOM = 19,
    //Pide la lista de usuarios.
    ROOM_USERS = 20,
    //Manda un mensaje a la sala.
    ROOM_TEXT = 21,
    //Abandona una sala.
    LEAVE_ROOM = 22,
    //El usuario se desconecta.
    DISCONNECT = 23
  };
  static std::string getString(TipoCliente::Tipo);
};

#endif 
