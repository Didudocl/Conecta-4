# Cliente de Conecta 4

Este archivo contiene la implementación del cliente para el juego de Conecta 4. El cliente se conecta al servidor, interactúa con él enviando jugadas y recibiendo actualizaciones del estado del juego. El cliente muestra el tablero y permite al usuario introducir sus jugadas.

## Bibliotecas Utilizadas

- `iostream`: Operaciones de entrada y salida estándar.
- `cstring`: Operaciones con cadenas de caracteres.
- `unistd.h`: Funciones de Unix (e.g., cierre de sockets).
- `sys/socket.h`: Operaciones de sockets.
- `sys/types.h`: Tipos de datos de sockets.
- `netinet/in.h`: Operaciones con direcciones de Internet.
- `arpa/inet.h`: Conversiones de direcciones de Internet.
- `cstdlib`: Funciones generales (e.g., atoi).
- `ctime`: Funciones de tiempo (e.g., time).

## Funcionalidades Principales

- Creación y configuración del socket del cliente.
- Conexión al servidor.
- Envío de jugadas al servidor.
- Recepción y visualización del estado del tablero.
- Interacción con el usuario para ingresar jugadas.
