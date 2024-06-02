#include <iostream>       // Operaciones de entrada y salida
#include <cstring>        // Operaciones con cadenas de caracteres
#include <unistd.h>       // Funciones de Unix (e.g., cierre de sockets)
#include <sys/socket.h>   // Operaciones de sockets
#include <sys/types.h>    // Tipos de datos de sockets
#include <netinet/in.h>   // Operaciones con direcciones de Internet
#include <arpa/inet.h>    // Conversiones de direcciones de Internet
#include <vector>         // Uso de vectores (arrays dinámicos)
#include <cstdlib>        // Funciones generales (e.g., srand, rand)
#include <ctime>          // Funciones de tiempo (e.g., time)
#include <thread>         // Manejo de hilos (threads)
#include <algorithm>      // Algoritmos estándar (e.g., std::find)
#include "board.cpp"      // Inclusión del archivo del tablero

// Clase del servidor
class Server {
private:
    int sockfd;  // Descriptor de socket del servidor
    struct sockaddr_in serverAddr;  // Dirección del servidor

public:
    // Constructor del servidor
    Server(int port) {
        std::srand(std::time(nullptr));  // Inicializar el generador de números aleatorios

        sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Crear socket del servidor
        if (sockfd < 0) {
            std::cerr << "[❌] Error en la conexión." << std::endl;
            exit(1);
        }
        std::cout << "[✔️] Socket del servidor creado." << std::endl;

        memset(&serverAddr, '\0', sizeof(serverAddr));  // Configurar dirección del servidor
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        int ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));  // Enlazar el socket del servidor a la dirección
        if (ret < 0) {
            std::cerr << "[❌] Error en el enlace." << std::endl;
            exit(1);
        }
        std::cout << "Esperando conexiones ..." << std::endl;

        if (listen(sockfd, 10) == 0) {  // Poner el servidor en modo de escucha
            std::cout << "[🎧] Escuchando en el puerto " << port << "..." << std::endl;
        } else {
            std::cerr << "[❌] Error en la escucha." << std::endl;
        }
    }

    // Enviar el estado del tablero a los clientes
    void sendBoardState(const Board& board, int clientSocket) {
        std::string boardState = "\n\n== Conecta 4 ==\n";  // Añadir nueva línea inicial
        boardState += board.toString();
        send(clientSocket, boardState.c_str(), boardState.size(), 0);
    }

    // Manejar una conexión de cliente
    void handleClient(int clientSocket, std::string clientIp, int clientPort) {
        Board board;  // Crear una instancia del tablero
        char buffer[1024];  // Buffer para recibir mensajes
        bool isClientTurn = (std::rand() % 2) == 0;  // Decidir al azar quién comienza
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: " << (isClientTurn ? "inicia juego el cliente." : "inicia juego el servidor.") << std::endl;

        sendBoardState(board, clientSocket);  // Enviar el estado inicial del tablero al cliente

        while (true) {
            if (isClientTurn) {
                memset(buffer, 0, sizeof(buffer));  // Limpiar el buffer
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);  // Recibir jugada del cliente
                if (bytesReceived > 0) {
                    int col = std::atoi(buffer);  // Convertir el mensaje a entero
                    if (col == 21) {  // Verificar si se pide empate
                        if (board.isFull()) {
                            std::string drawMessage = "¡Empate!";
                            send(clientSocket, drawMessage.c_str(), drawMessage.size(), 0);
                            std::cout << "Juego [" << clientIp << ":" << clientPort << "]: empate." << std::endl;
                            break;
                        } else {
                            std::string continueMessage = "El juego no está lleno, no es un empate.";
                            send(clientSocket, continueMessage.c_str(), continueMessage.size(), 0);
                            continue;
                        }
                    }
                    board.dropPiece(col, 'C');  // 'C' representa al cliente
                    std::cout << "Juego [" << clientIp << ":" << clientPort << "]: cliente juega columna " << col << "." << std::endl;
                } else {
                    std::cerr << "[❌] Conexión perdida." << std::endl;
                    break;
                }
            } else {
                int col = std::rand() % 7;  // Jugada aleatoria del servidor
                board.dropPiece(col, 'S');  // 'S' representa al servidor
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: servidor juega columna " << col << "." << std::endl;
            }

            sendBoardState(board, clientSocket);  // Enviar el estado actualizado del tablero al cliente

            // Verificar si el juego ha terminado
            if (board.checkWin('C')) {
                std::string winMessage = "¡Has ganado!";
                send(clientSocket, winMessage.c_str(), winMessage.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: gana cliente." << std::endl;
                break;
            } else if (board.checkWin('S')) {
                std::string winMessage = "¡El servidor ha ganado!";
                send(clientSocket, winMessage.c_str(), winMessage.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: gana servidor." << std::endl;
                break;
            }

            if (board.isFull()) {  // Verificar si el tablero está lleno (empate)
                std::string drawMessage = "¡Empate!";
                send(clientSocket, drawMessage.c_str(), drawMessage.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: empate." << std::endl;
                break;
            }

            isClientTurn = !isClientTurn;  // Cambiar turno después de verificar el estado del juego
        }
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: fin del juego." << std::endl;
        close(clientSocket);  // Cerrar socket del cliente
    }

    // Iniciar el servidor
    void start() {
        while (true) {
            struct sockaddr_in newAddr;  // Dirección del nuevo cliente
            socklen_t addr_size = sizeof(newAddr);
            int newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);  // Aceptar conexión del cliente
            if (newSocket < 0) {
                std::cerr << "[❌] Error en la aceptación." << std::endl;
                exit(1);
            }

            char clientIp[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &newAddr.sin_addr, clientIp, INET_ADDRSTRLEN);  // Convertir IP a cadena
            int clientPort = ntohs(newAddr.sin_port);

            std::cout << "Juego nuevo [" << clientIp << ":" << clientPort << "]." << std::endl;

            std::thread(&Server::handleClient, this, newSocket, std::string(clientIp), clientPort).detach();  // Crear un nuevo hilo para manejar el cliente
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <puerto>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);  // Convertir el argumento de puerto a entero
    Server server(port);  // Crear instancia del servidor
    server.start();  // Iniciar el servidor
    return 0;
}
