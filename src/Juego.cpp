#include "../include/Juego.hpp"
#include <iostream>
#include <limits>

Juego::Juego(int filas, int columnas, int minas) {
    tablero = nullptr;
    jugador = nullptr;
    renderizador = nullptr;
}

Juego::~Juego() {
}

void Juego::iniciar() {
    std::cout << "Bienvenido a Buscaminas!" << std::endl;

    // Inicialización básica
    int filas = 5, columnas = 5, minas = 3;
    delete tablero;
    tablero = new Tablero(filas, columnas, minas);

    int puntaje = 0;
    bool jugando = true;
    while (jugando) {
        tablero->imprimirTablero(false);

        int fila, columna;
        std::cout << "Ingresa la fila (0-" << filas-1 << "): ";
        std::cin >> fila;
        std::cout << "Ingresa la columna (0-" << columnas-1 << "): ";
        std::cin >> columna;

        // Validar entrada
        if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
            std::cout << "Coordenadas fuera de rango. Intenta de nuevo." << std::endl;
            continue;
        }

        if (tablero->esMina(fila, columna)) {
            tablero->revelarCelda(fila, columna);
            tablero->imprimirTablero(true);
            std::cout << "¡BOOM! Pisaste una mina. Fin del juego." << std::endl;
            jugando = false;
        } else if (!tablero->celdaEstaRevelada(fila, columna)) {
            tablero->revelarCelda(fila, columna);
            puntaje++;
            if (tablero->estaDespejado()) {
                tablero->imprimirTablero(true);
                std::cout << "¡Felicidades! Has despejado el tablero." << std::endl;
                jugando = false;
            }
        } else {
            std::cout << "Esa celda ya fue revelada." << std::endl;
        }
    }
    std::cout << "Tu puntaje final: " << puntaje << std::endl;
}