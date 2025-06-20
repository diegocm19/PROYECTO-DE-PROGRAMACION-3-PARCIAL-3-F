#pragma once
#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Renderizador.hpp"

class Juego {
private:
    Tablero* tablero;
    Jugador* jugador;
    Renderizador* renderizador;
public:
    Juego(int filas, int columnas, int minas);
    ~Juego();
    void iniciar();
};