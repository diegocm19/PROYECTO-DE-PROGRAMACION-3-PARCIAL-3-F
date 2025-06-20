#pragma once

class Jugador {
private:
    int movimientos;
public:
    Jugador();
    void incrementarMovimientos();
    int obtenerMovimientos() const;
};