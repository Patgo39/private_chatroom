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
ninja -C builddir
```

## Ejecución del proyecto

Para ejecutar el servidor y el cliente, utiliza los siguientes comandos:

```bash
./builddir/Servidor
./builddir/Cliente
```

## Comandos para la Ejecución

Para interactuar con el servidor, utiliza los siguientes comandos:
- `/identify "username"`  // Cambia el estado del usuario
- `/status "new_status"`  // Cambia el estado del usuario
- `/list`  // Obtiene la lista de usuarios.
- `/private "username" text...`  // Envía un texto privado.
- `/new "Room name"`  // Crea un cuarto.
- `/invite "Room name" "usuario1" "usuario2" "usuario3" ...`  // Invita usuarios a una sala.
- `/join "Nombre de la sala"`  // El usuario se une a una sala.
- `/room "Nombre de la sala"`  // Pide la lista de usuarios de la sala
- `/leave "Nombre de la sala"`  // El usuario abandona la sala
- `/disconnect`  // Desconecta al usuario

## Autor

Patricio García Ocampo

## Notas Extras

El sistema no tiene implementado por completo los cuartos y falla si no recibe un JSON.

