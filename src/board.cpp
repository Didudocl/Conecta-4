#include <vector>  // Biblioteca para usar vectores
#include <string>  // Biblioteca para usar cadenas de caracteres

// Clase que representa el tablero del juego
class Board {
private:
    int rows;  // Número de filas
    int cols;  // Número de columnas
    std::vector<std::vector<char>> grid;  // Matriz que representa el tablero

public:
    // Constructor que inicializa el tablero con espacios vacíos
    Board(int r = 6, int c = 7) : rows(r), cols(c), grid(r, std::vector<char>(c, ' ')) {}

    // Método para colocar una ficha en una columna
    bool dropPiece(int col, char piece) {
        if (col < 0 || col >= cols) return false;  // Verifica si la columna es válida
        for (int row = rows - 1; row >= 0; --row) {  // Recorre la columna de abajo hacia arriba
            if (grid[row][col] == ' ') {  // Encuentra la primera celda vacía
                grid[row][col] = piece;  // Coloca la ficha
                return true;  // Movimiento exitoso
            }
        }
        return false;  // Columna llena
    }

    // Método para verificar si hay un ganador
    bool checkWin(char piece) const {
        // Verificar horizontal
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols - 3; ++col) {
                if (grid[row][col] == piece && grid[row][col + 1] == piece &&
                    grid[row][col + 2] == piece && grid[row][col + 3] == piece) {
                    return true;
                }
            }
        }
        // Verificar vertical
        for (int col = 0; col < cols; ++col) {
            for (int row = 0; row < rows - 3; ++row) {
                if (grid[row][col] == piece && grid[row + 1][col] == piece &&
                    grid[row + 2][col] == piece && grid[row + 3][col] == piece) {
                    return true;
                }
            }
        }
        // Verificar diagonal descendente
        for (int row = 0; row < rows - 3; ++row) {
            for (int col = 0; col < cols - 3; ++col) {
                if (grid[row][col] == piece && grid[row + 1][col + 1] == piece &&
                    grid[row + 2][col + 2] == piece && grid[row + 3][col + 3] == piece) {
                    return true;
                }
            }
        }
        // Verificar diagonal ascendente
        for (int row = 3; row < rows; ++row) {
            for (int col = 0; col < cols - 3; ++col) {
                if (grid[row][col] == piece && grid[row - 1][col + 1] == piece &&
                    grid[row - 2][col + 2] == piece && grid[row - 3][col + 3] == piece) {
                    return true;
                }
            }
        }
        return false;  // No hay ganador
    }

    // Método para verificar si el tablero está lleno
    bool isFull() const {
        for (int col = 0; col < cols; ++col) {
            if (grid[0][col] == ' ') {
                return false;  // Encontró una celda vacía
            }
        }
        return true;  // Todas las celdas están llenas
    }

    // Método para convertir el tablero a una cadena de caracteres
    std::string toString() const {
        std::string boardStr;
        for (int row = 0; row < rows; ++row) {
            boardStr += std::to_string(row) + " ";  // Añadir el número de la fila
            for (int col = 0; col < cols; ++col) {
                boardStr += grid[row][col];  // Añadir el valor de la celda
                boardStr += " ";  // Espacio entre celdas
            }
            boardStr += "\n";  // Nueva línea al final de la fila
        }
        boardStr += "-------------\n  0 1 2 3 4 5 6 \n";  // Añadir la numeración de las columnas
        return boardStr;  // Devolver la representación del tablero
    }
};
