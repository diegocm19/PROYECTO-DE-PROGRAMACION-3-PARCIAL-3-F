#include "../include/Celda.hpp"

Celda::Celda() {
    tieneMina = false;
    revelada = false;
    marcada = false;
    minasAdyacentes = 0;
}

void Celda::ponerMina() {
    tieneMina = true;
}

bool Celda::obtenerMina() const {
    return tieneMina;
}

void Celda::revelar() {
    revelada = true;
}

bool Celda::estaRevelada() const {
    return revelada;
}

void Celda::alternarBandera() {
    marcada = !marcada;
}

bool Celda::estaMarcada() const {
    return marcada;
}

void Celda::establecerMinasAdyacentes(int cantidad) {
    minasAdyacentes = cantidad;
}

int Celda::obtenerMinasAdyacentes() const {
    return minasAdyacentes;
}