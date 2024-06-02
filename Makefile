# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -std=c++11

# Directorios
SRC_DIR = src
BUILD_DIR = build

# Archivos fuente
CLIENT_SRC = $(SRC_DIR)/client.cpp
SERVER_SRC = $(SRC_DIR)/server.cpp
BOARD_SRC = $(SRC_DIR)/board.cpp

# Archivos objeto
CLIENT_OBJ = $(BUILD_DIR)/client.o
SERVER_OBJ = $(BUILD_DIR)/server.o
BOARD_OBJ = $(BUILD_DIR)/board.o

# Ejecutables
CLIENT_EXEC = client
SERVER_EXEC = server

# Regla por defecto
all: $(CLIENT_EXEC) $(SERVER_EXEC)

# Regla para compilar el cliente
$(CLIENT_EXEC): $(CLIENT_OBJ) $(BOARD_OBJ)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJ) $(BOARD_OBJ)

# Regla para compilar el servidor
$(SERVER_EXEC): $(SERVER_OBJ) $(BOARD_OBJ)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJ) $(BOARD_OBJ)

# Regla para crear el archivo objeto del cliente
$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

# Regla para crear el archivo objeto del servidor
$(SERVER_OBJ): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)

# Regla para crear el archivo objeto del tablero
$(BOARD_OBJ): $(BOARD_SRC)
	$(CXX) $(CXXFLAGS) -c $(BOARD_SRC) -o $(BOARD_OBJ)

# Limpiar archivos compilados
clean:
	rm -f $(BUILD_DIR)/*.o $(CLIENT_EXEC) $(SERVER_EXEC)

# Crear directorio de build si no existe
$(shell mkdir -p $(BUILD_DIR))

.PHONY: all clean run
