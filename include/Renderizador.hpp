#pragma once
#include "Tablero.hpp"

class Renderizador {
public:
    Renderizador();
    void renderizar(const Tablero& tablero, bool revelarTodo = false) const;
    void mostrarMensaje(const char* mensaje) const;
};