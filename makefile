# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

CXXFLAGS := -std=c++17 -Wall
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Nombre del ejecutable
TARGET := $(BIN_DIR)/ThePong.exe

# Regla para compilar todo el proyecto
all: $(TARGET)

$(TARGET): $(CPP_FILES)
	@mkdir -p $(BIN_DIR)
	g++ $(CXXFLAGS) $(CPP_FILES) -Iinclude -o $(TARGET) $(SFML)

# Regla para ejecutar
run: $(TARGET)
	./$(TARGET)


# Limpiar
clean:
	rm -f $(TARGET)

.PHONY: all clean run