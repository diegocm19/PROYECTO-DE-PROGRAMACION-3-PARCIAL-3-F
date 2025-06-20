#include "../include/Tablero.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Tablero::Tablero(int filas_, int columnas_, int minas_) {
    filas = filas_;
    columnas = columnas_;
    minas = minas_;
    celdas.resize(filas, std::vector<Celda*>(columnas, nullptr));
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            celdas[i][j] = new Celda();

    // Colocar minas aleatoriamente
    srand((unsigned)time(0));
    int colocadas = 0;
    while (colocadas < minas) {
        int f = rand() % filas;
        int c = rand() % columnas;
        if (!celdas[f][c]->obtenerMina()) {
            celdas[f][c]->ponerMina();
            colocadas++;
        }
    }

    // Calcular minas adyacentes para cada celda
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (celdas[i][j]->obtenerMina()) {
                celdas[i][j]->establecerMinasAdyacentes(-1);
                continue;
            }
            int cuenta = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas)
                        if (celdas[ni][nj]->obtenerMina())
                            cuenta++;
                }
            }
            celdas[i][j]->establecerMinasAdyacentes(cuenta);
        }
    }
}

Tablero::~Tablero() {
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            delete celdas[i][j];
}

void Tablero::revelarCelda(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
        return;
    if (celdas[fila][columna]->estaRevelada() || celdas[fila][columna]->estaMarcada())
        return;
    celdas[fila][columna]->revelar();
    if (celdas[fila][columna]->obtenerMinasAdyacentes() == 0 && !celdas[fila][columna]->obtenerMina()) {
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di != 0 || dj != 0)
                    revelarCelda(fila + di, columna + dj);
            }
        }
    }
}

void Tablero::alternarBandera(int fila, int columna) {
    celdas[fila][columna]->alternarBandera();
}

bool Tablero::esMina(int fila, int columna) const {
    return celdas[fila][columna]->obtenerMina();
}

bool Tablero::estaDespejado() const {
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            if (!celdas[i][j]->obtenerMina() && !celdas[i][j]->estaRevelada())
                return false;
    return true;
}

void Tablero::imprimirTablero(bool revelarTodo) const {
    std::cout << "  ";
    for (int j = 0; j < columnas; ++j)
        std::cout << j << " ";
    std::cout << std::endl;
    for (int i = 0; i < filas; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < columnas; ++j) {
            if (revelarTodo || celdas[i][j]->estaRevelada()) {
                if (celdas[i][j]->obtenerMina())
                    std::cout << "* ";
                else
                    std::cout << celdas[i][j]->obtenerMinasAdyacentes() << " ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << std::endl;
    }
}

bool Tablero::celdaEstaRevelada(int fila, int columna) const {
    return celdas[fila][columna]->estaRevelada();
}