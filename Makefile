CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall
SRC = src/main.cpp src/Juego.cpp src/Tablero.cpp src/Celda.cpp src/Jugador.cpp src/Renderizador.cpp
BIN = bin/buscaminas.exe

# Cambia esta ruta por la ruta real donde tienes SFML
SFML_INCLUDE = -IC:/Users/luise/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit/SFML-2.5.1/include
SFML_LIB = -LC:/Users/luise/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(BIN)

$(BIN): $(SRC)
	if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: all
	$(BIN)

clean:
	if exist bin rmdir /s /q bin
	rm -rf bin *.o

sfml: src/VentanaSFML.cpp
	if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) src/VentanaSFML.cpp -o bin/ventana_sfml.exe $(SFML_LIB)
