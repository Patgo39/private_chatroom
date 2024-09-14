# Chatroom Proyecto 1 Modelado y Programación

Este proyecto es una aplicación de chat en tiempo real que incluye un servidor y un cliente para la comunicación entre usuarios. Está diseñado para manejar múltiples usuarios, salas de chat y mensajes privados y públicos.

## Clonación del Repositorio

Para clonar el repositorio, utiliza el siguiente comando:

```bash
git clone https://gitlab.com/patriciogarcia321/proyecto1myp
```

## Configuración del proyecto

En las carpetas `servidor/` y `cliente/`, ejecuta los siguientes comandos para configurar y compilar el proyecto:

```bash
meson setup builddir
meson compile -C builddir
```

## Ejecución del proyecto

Para ejecutar el servidor y el cliente, utiliza los siguientes comandos:

```bash
./builddir/Servidor
./builddir/Cliente
```

## Comandos para la Ejecución

Para interactuar con el servidor, utiliza los siguientes comandos:

- `REQUEST -s "new_status"`  // STATUS Cambia el estado del usuario
- `REQUEST -u`  // USERS Obtiene la lista de usuarios.
- `REQUEST -t "Nombre del usuario" texto ...`  // TEXT Envía un texto privado.
- `REQUEST -nr "Nombre de la sala"`  // NEW_ROOM Crea una sala
- `REQUEST -i "nombre de la sala" | "usuario1" "usuario2" "usuario3" ...`  // INVITE Invita usuarios a una sala.
- `REQUEST -jr "Nombre de la sala"`  // JOIN_ROOM El usuario se une a una sala.
- `REQUEST -ru "Nombre de la sala"`  // ROOM_USERS Pide la lista de usuarios de la sala
- `REQUEST -lr "Nombre de la sala"`  // LEAVE_ROOM El usuario abandona la sala
- `REQUEST -d`  // DISCONNECT Desconecta al usuario

## Autor

Patricio García Ocampo

