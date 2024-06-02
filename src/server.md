# Servidor de Conecta 4

Este archivo contiene la implementación del servidor para el juego de Conecta 4 utilizando sockets y hilos para manejar múltiples conexiones de clientes de forma concurrente. El servidor permite que los clientes se conecten y jueguen turnos alternativos, gestionando el estado del tablero y determinando el resultado del juego (victoria, derrota o empate).

## Bibliotecas Utilizadas

- `iostream`: Operaciones de entrada y salida estándar.
- `cstring`: Operaciones con cadenas de caracteres.
- `unistd.h`: Funciones de Unix (e.g., cierre de sockets).
- `sys/socket.h`: Operaciones de sockets.
- `sys/types.h`: Tipos de datos de sockets.
- `netinet/in.h`: Operaciones con direcciones de Internet.
- `arpa/inet.h`: Conversiones de direcciones de Internet.
- `vector`: Uso de vectores (arrays dinámicos).
- `cstdlib`: Funciones generales (e.g., srand, rand).
- `ctime`: Funciones de tiempo (e.g., time).
- `thread`: Manejo de hilos (threads).
- `algorithm`: Algoritmos estándar (e.g., std::find).

## Funcionalidades Principales

- Creación y configuración del socket del servidor.
- Aceptación de conexiones de clientes.
- Manejo de múltiples clientes concurrentemente utilizando hilos.
- Gestión del estado del juego y del tablero.
- Verificación de condiciones de victoria, derrota y empate.
