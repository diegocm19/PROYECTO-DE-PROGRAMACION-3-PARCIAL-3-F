#pragma once

class Celda {
private:
    bool tieneMina;
    bool revelada;
    bool marcada;
    int minasAdyacentes;
public:
    Celda();
    void ponerMina();
    bool obtenerMina() const;
    void revelar();
    bool estaRevelada() const;
    void alternarBandera();
    bool estaMarcada() const;
    void establecerMinasAdyacentes(int cantidad);
    int obtenerMinasAdyacentes() const;
};