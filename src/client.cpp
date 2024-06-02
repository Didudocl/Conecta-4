#include <iostream> // Biblioteca para operaciones de entrada y salida
#include <cstring> // Biblioteca para operaciones con cadenas de caracteres
#include <unistd.h> // Biblioteca para operaciones de Unix (e.g., cierre de sockets)
#include <sys/socket.h> // Biblioteca para operaciones de sockets
#include <sys/types.h> // Biblioteca para tipos de datos de sockets
#include <netinet/in.h> // Biblioteca para operaciones con direcciones de internet
#include <arpa/inet.h> // Biblioteca para conversiones de direcciones de internet
#include <cstdlib> // Biblioteca para funciones generales (e.g., atoi)
#include <ctime> // Biblioteca para funciones de tiempo (e.g., time)

int main(int argc, char* argv[]) {
    // Verificar si se proporcionaron los argumentos necesarios
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <IP del servidor> <puerto>" << std::endl;
        return 1;
    }

    // Obtener la IP del servidor y el puerto desde los argumentos
    const char* serverIp = argv[1];
    int port = std::atoi(argv[2]);

    int clientSocket; // Descriptor de socket del cliente
    struct sockaddr_in serverAddr; // Dirección del servidor
    char buffer[1024]; // Buffer para recibir mensajes

    // Crear socket del cliente
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "[❌] Error en la conexión." << std::endl;
        return -1;
    }
    std::cout << "[✔️] Socket del cliente creado." << std::endl;

    // Configurar la dirección del servidor
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    // Conectarse al servidor
    int ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        std::cerr << "[❌] Error en la conexión al servidor." << std::endl;
        return -1;
    }
    std::cout << "[🔗] Conectado al servidor." << std::endl;

    // Interacción con el servidor
    while (true) {
        // Recibir y mostrar el estado del tablero
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "" << buffer << std::endl;

            // Verificar si el juego ha terminado
            if (strstr(buffer, "¡Has ganado!") != nullptr || strstr(buffer, "¡El servidor ha ganado!") != nullptr || strstr(buffer, "¡Empate!") != nullptr) {
                std::cout << "[🏁] Fin del juego." << std::endl;
                break;  // Salir del bucle si el juego ha terminado
            }
        } else {
            std::cerr << "[❌] Conexión perdida." << std::endl;
            break;
        }

        // Enviar la jugada del cliente
        std::cout << "Ingresa la columna (0-6) donde deseas colocar tu ficha: ";
        int col;
        std::cin >> col;
        std::string message = std::to_string(col);
        send(clientSocket, message.c_str(), message.size(), 0);
    }

    // Cerrar el socket del cliente
    close(clientSocket);
    return 0;
}
