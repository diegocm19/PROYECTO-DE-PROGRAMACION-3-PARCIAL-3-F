#include <windows.h>
#include "../include/VentanaSFML.hpp"
#include "../include/Tablero.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

const int FILAS = 8;
const int COLUMNAS = 8;
const int MINAS = 10;
const int TAM_CELDA = 40;

// Función para dibujar un botón y devolver true si se hace clic
bool dibujarBoton(sf::RenderWindow& window, const std::string& texto, int x, int y, int w, int h, sf::Font& font, sf::Event& event) {
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(180, 180, 180));
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    window.draw(rect);
    sf::Text t(texto, font, 22);
    t.setFillColor(sf::Color::Black);
    t.setPosition(x + 15, y + 8);
    window.draw(t);
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        int mx = event.mouseButton.x, my = event.mouseButton.y;
        if (mx >= x && mx <= x + w && my >= y && my <= y + h) return true;
    }
    return false;
}

void ejecutarVentanaSFML() {
    sf::RenderWindow window(sf::VideoMode(COLUMNAS * TAM_CELDA, FILAS * TAM_CELDA), "Buscaminas SFML", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    sf::Font font;
    if (!font.loadFromFile("data/arial.ttf")) {
        std::cerr << "[ERROR] No se pudo cargar la fuente data/arial.ttf. El texto no se mostrará correctamente." << std::endl;
    }

    // Cargar texturas
    sf::Texture texCerrada, texRevelada, texMina, texBandera;
    texCerrada.loadFromFile("data/oculta.png");
    texRevelada.loadFromFile("data/descubierta.png");
    texMina.loadFromFile("data/mina.png");
    texBandera.loadFromFile("data/bandera.png");
    std::map<int, sf::Texture> texNumeros;
    for (int n = 1; n <= 8; ++n) {
        sf::Texture tex;
        tex.loadFromFile("data/" + std::to_string(n) + ".png");
        texNumeros[n] = tex;
    }

    bool enMenu = true;
    bool jugando = false;
    bool gameOver = false, victoria = false;
    Tablero tablero(FILAS, COLUMNAS, MINAS);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (enMenu) {
                window.clear(sf::Color(200, 200, 200));
                // Título del juego
                sf::Text titulo("Buscaminas", font, 36);
                titulo.setFillColor(sf::Color(50, 50, 150));
                titulo.setStyle(sf::Text::Bold);
                titulo.setPosition(40, 20);
                window.draw(titulo);
                if (dibujarBoton(window, "Jugar", 60, 80, 120, 40, font, event)) {
                    tablero = Tablero(FILAS, COLUMNAS, MINAS);
                    jugando = true;
                    enMenu = false;
                    gameOver = false;
                    victoria = false;
                }
                if (dibujarBoton(window, "Salir", 60, 140, 120, 40, font, event)) {
                    window.close();
                }
                window.display();
            } else if (jugando && !gameOver && event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / TAM_CELDA;
                int y = event.mouseButton.y / TAM_CELDA;
                if (x >= 0 && x < COLUMNAS && y >= 0 && y < FILAS) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (!tablero.celdaEstaRevelada(y, x) && !tablero.celdaEstaMarcada(y, x)) {
                            tablero.revelarCelda(y, x);
                            if (tablero.esMina(y, x)) {
                                gameOver = true;
                            } else if (tablero.estaDespejado()) {
                                victoria = true;
                                gameOver = true;
                            }
                        }
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        tablero.alternarBandera(y, x);
                    }
                }
            } else if (gameOver && event.type == sf::Event::MouseButtonPressed) {
                window.clear(sf::Color(200, 200, 200));
                std::string msg = victoria ? "¡Ganaste!" : "¡Perdiste!";
                sf::Text t(msg, font, 28);
                t.setFillColor(sf::Color::Black);
                t.setPosition(60, 30);
                window.draw(t);
                if (dibujarBoton(window, "Reintentar", 60, 80, 120, 40, font, event)) {
                    tablero = Tablero(FILAS, COLUMNAS, MINAS);
                    jugando = true;
                    gameOver = false;
                    victoria = false;
                }
                if (dibujarBoton(window, "Salir", 60, 140, 120, 40, font, event)) {
                    window.close();
                }
                window.display();
            }
        }
        if (jugando) {
            window.clear(sf::Color(200, 200, 200));
            for (int i = 0; i < FILAS; ++i) {
                for (int j = 0; j < COLUMNAS; ++j) {
                    sf::Sprite sprite;
                    if (tablero.celdaEstaRevelada(i, j)) {
                        if (tablero.esMina(i, j)) {
                            sprite.setTexture(texMina);
                        } else {
                            int minasAdj = tablero.obtenerMinasAdyacentes(i, j);
                            if (minasAdj > 0 && minasAdj <= 8) {
                                sprite.setTexture(texNumeros[minasAdj]);
                            } else {
                                sprite.setTexture(texRevelada);
                            }
                        }
                    } else if (tablero.celdaEstaMarcada(i, j)) {
                        sprite.setTexture(texBandera);
                    } else {
                        sprite.setTexture(texCerrada);
                    }
                    sprite.setPosition(j * TAM_CELDA, i * TAM_CELDA);
                    if (sprite.getTexture()) {
                        float scaleX = TAM_CELDA / static_cast<float>(sprite.getTexture()->getSize().x);
                        float scaleY = TAM_CELDA / static_cast<float>(sprite.getTexture()->getSize().y);
                        sprite.setScale(scaleX, scaleY);
                    }
                    window.draw(sprite);
                }
            }
            window.display();
            if (gameOver) {
                jugando = false;
            }
        }
    }
}
