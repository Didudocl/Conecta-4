# Conecta 4 con Sockets y Concurrencia

Este proyecto implementa el juego de Conecta 4 utilizando sockets y concurrencia en C++. El servidor maneja múltiples conexiones de clientes utilizando hilos (threads), permitiendo que varios clientes jueguen simultáneamente.

## Alumnos

- Diego Alexis Salazar Jara
- Francisco Ramón Ojeda Casanueva

## Instrucciones de Compilación

Para compilar el proyecto, asegúrate de tener `g++` instalado. Luego, sigue estos pasos:

1. Compilar el proyecto:

    ```bash
    make
    ```

2. Limpiar los archivos de compilación (en caso de que se requiera):

    ```bash
    make clean
    ```

## Instrucciones de Ejecución

1. Iniciar el servidor:

    ```bash
    ./server <puerto>
    ```

    Reemplaza `<puerto>` con el número de puerto que deseas usar.

2. Iniciar el cliente:

    ```bash
    ./client 127.0.0.1 <puerto>
    ```

    Reemplaza `<puerto>` con el mismo número de puerto que usaste para el servidor.

## Archivos de Documentación

- [Servidor](./src/server.md): Documentación del servidor de Conecta 4.
- [Cliente](./src/client.md): Documentación del cliente de Conecta 4.

  ⌨️ with ❤️ by [@Didudocl](https://github.com/Didudocl) y [@Metalcl](https://github.com/Metalcl) 
