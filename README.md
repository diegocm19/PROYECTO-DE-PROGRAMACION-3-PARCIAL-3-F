# PROYECTO-DE-PROGRAMACION-3-PARCIAL-3-F
# Buscaminas SFML

Este proyecto es una implementación gráfica del clásico juego **Buscaminas** usando C++ y la biblioteca **SFML**.

## Características
- Interfaz gráfica con SFML.
- Tablero de 8x8 con 10 minas.
- Clic izquierdo para revelar celdas.
- Clic derecho para colocar o quitar banderas.
- Revelado en cascada de celdas vacías.
- Menú de inicio con opciones para jugar o salir.
- Opción de reintentar o salir al terminar la partida.
- Imágenes personalizadas para celdas, minas, banderas y números.

## Requisitos
- **SFML 2.5.1** (o compatible) para MinGW 32-bit.
- Compilador compatible con C++11 o superior (recomendado MinGW).
- Archivo de fuente `arial.ttf` en la carpeta `data`.

## Estructura del proyecto
```
Proyecto-tercer-parcial-programacion/
├── bin/
│   └── buscaminas.exe
├── data/
│   ├── 1.png ... 8.png
│   ├── bandera.png
│   ├── descubierta.png
│   ├── mina.png
│   ├── oculta.png
│   └── arial.ttf
├── include/
│   ├── Celda.hpp
│   ├── Juego.hpp
│   ├── Jugador.hpp
│   ├── Renderizador.hpp
│   ├── Tablero.hpp
│   └── VentanaSFML.hpp
├── src/
│   ├── Celda.cpp
│   ├── Juego.cpp
│   ├── Jugador.cpp
│   ├── main.cpp
│   ├── Renderizador.cpp
│   ├── Tablero.cpp
│   └── VentanaSFML.cpp
└── README.md
```

## Cómo compilar

1. Asegúrate de tener SFML instalado y las DLLs en la carpeta `bin`.
2. Coloca las imágenes y la fuente en la carpeta `data`.
3. Compila con:

```sh
# En PowerShell o CMD
 g++ -o bin/buscaminas.exe src/*.cpp -Iinclude -IC:/ruta/a/SFML/include -LC:/ruta/a/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
```

## Cómo jugar
- Ejecuta el programa: `./bin/buscaminas.exe`
- Haz clic en "Jugar" en el menú.
- Usa el mouse para jugar:
  - **Clic izquierdo:** Revelar celda.
  - **Clic derecho:** Colocar/quitar bandera.
- Al terminar, puedes reintentar o salir desde el menú.

## Créditos
- Diego Caravantes Mares
- Luis Eduardo Lopez Garcia

---

