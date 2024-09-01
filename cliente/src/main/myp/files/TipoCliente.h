/* TipoCliente es una enumeración que contempla todas las solicitudes que un
 * usuario puede hacer al servidor.
 */
#ifndef TIPOCLIENTE_H
#define TIPOCLIENTE_H

/* Cada tipo está asociado a un número negativo con el fin de evitar posibles
 * conflictos con el código.
 * Los números asociados son multipos de 10.
 */
enum class TipoCliente{
  //Se identifica el ussuario.
  IDENTIFY = -10,
  //Cambia el estatus del ususario.
  STATUS = -20,
  //Pide la lista de usuarios.
  USERS = -30,
  //Manda texto privado a un usuario,
  TEXT = -40,
  //Manda un mensaje publico.
  PUBLIC_TEX = -50,
  //Crea una nueva sala.
  NEW_ROOM = -60;
  //Invita a uno o más usuarios a una sala.
  INVITE= -70,
  //El usuario se une a una sala.
  JOIN_ROOM = -80,
  //Pide la lista de usuarios.
  ROOM_USERS = -90,
  //Manda un mensaje a la sala.
  ROOM_TEXT = -100,
  //Abandona una sala.
  LEAVE_ROOM = -110,
  //El usuario se desconecta.
  DISCONNECT = -120
};

#endif 
