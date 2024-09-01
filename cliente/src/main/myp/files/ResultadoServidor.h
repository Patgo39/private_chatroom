/* RespuestaServidor es una enumeración son los resultados de las peticiones
 * del ususario. En su mayoría van en compañía de la enumeración TipoServidor.
 */
#ifndef RESULTADOSERVIDOR_H
#define RESULTADOSERVIDOR_H

/* No hay una regla en especifico para estos valores de la enumeración. Algunos
 * son el TipoServidor con el que van acompañados más 1, otros el TipoCliente +  * 1. Otros simplemente fue elegir un número no usado.
 * Varios de los resultados son usados en distintas peticiones, por dicha razón
 * los valores no tienen orden ni regla.
 */
enum class ResultadoServidor{
  //Indica que una petición del usuario es exitosa.
  SUCCESS = -6,
    //Indica que el nombre de usuario ya está siendo usado.
    USER_ALREADY_EXISTS = -11,
    //Indica que el destinatario del mensaje o el usuario invitado no fue encontrado.
    NO_SUCH_USER = -46,
    //Indica que el cuarto ya existe.
    ROOM_ALREADY_EXISTS = -61,
    //Indica que la sala no existe al hacer una invitación o al momento de unirse o al momento de pedir la lista de usuarios o al momendo de enviar mensaje.
    //También cuando intenta dejar una sala que no existe.
    NO_SUCH_ROOM = -71,
    //Indica que el usuario no fue invitado.
    NOT_INVITED = -81,
    //Indica que el ususario no se ha unido a la sala o no ha sido invitadocuando pide la lista de usuarios o intenta dejar una sala en la que no está.
    NOT_JOINED = -91
    
};

#endif
