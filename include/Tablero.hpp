#pragma once
#include <vector>
#include "Celda.hpp"

class Tablero {
private:
    int filas, columnas, minas;
    std::vector<std::vector<Celda*>> celdas;
public:
    Tablero(int filas, int columnas, int minas);
    ~Tablero();
    void revelarCelda(int fila, int columna);
    void alternarBandera(int fila, int columna);
    bool esMina(int fila, int columna) const;
    bool estaDespejado() const;
    void imprimirTablero(bool revelarTodo = false) const;
    bool celdaEstaRevelada(int fila, int columna) const;
    bool celdaEstaMarcada(int fila, int columna) const {
        return celdas[fila][columna]->estaMarcada();
    }
    int obtenerMinasAdyacentes(int fila, int columna) const {
        return celdas[fila][columna]->obtenerMinasAdyacentes();
    }
};