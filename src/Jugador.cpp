#include "../include/Jugador.hpp"

Jugador::Jugador() {
    movimientos = 0;
}

void Jugador::incrementarMovimientos() {
    movimientos++;
}

int Jugador::obtenerMovimientos() const {
    return movimientos;
}