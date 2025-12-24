#include <iostream>
#include <raylib.h>
using namespace std;


// Un enum se utiliza para representar opciones fijas
// para no usar numeros raros
enum Direccion 
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};


int main()
{
    // -------------------------------------------------
    // CONCEPTO A RECORDAR:
    // En este juego usamos un GRID.
    // Para dibujar en pantalla, convertimos:
    // Celda × tamaño_de_celda = píxeles
    // -------------------------------------------------

    // Un struct se usa para agrupar valores relacionados.
    // En este caso, representa una posición (x, y) en el grid.
    struct Coordenadas
    {
        int x = 3; // posición horizontal en celdas
        int y = 4; // posición vertical en celdas
        int snake_pos_x = 6; //posicion de la comida
        int snake_pos_y = 4; //posicion de la comida
    };

    // Estos valores definen las reglas del mundo del juego.
    // NO son píxeles directamente.
    int tamano_de_celda = 25;      // tamaño de cada celda en píxeles
    int cantidad_de_celdas = 30;   // cuántas celdas hay en ancho y alto

    // Creamos una instancia del struct.
    // Esta variable representa la posición actual del snake en el grid.
    Coordenadas snake_posicion, snake_food_position;

    // Convertimos la posición del snake de celdas a píxeles.
    // Raylib dibuja usando píxeles, no celdas.
    int posicionX = snake_posicion.x * tamano_de_celda;
    int posicionY = snake_posicion.y * tamano_de_celda;

    // aqui convertimos la poscion de la comida de celsas a pixes 
    int snake_food_position_x = snake_food_position.snake_pos_x * tamano_de_celda;
    int snake_food_postion_y = snake_food_position.snake_pos_y * tamano_de_celda;

    // -------------------------------------------------
    // Inicialización de la ventana
    // El tamaño de la ventana depende del grid
    // -------------------------------------------------
    InitWindow(
        tamano_de_celda * cantidad_de_celdas,
        tamano_de_celda * cantidad_de_celdas,
        "Snake Game"
    );

    // Definimos cuántos frames por segundo tendrá el juego
    SetTargetFPS(60);

    // -------------------------------------------------
    // Bucle principal del juego
    // Mientras la ventana esté abierta, el juego sigue vivo
    // -------------------------------------------------
    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Limpiamos la pantalla antes de dibujar
        ClearBackground(BLACK);

        // Dibujamos el snake como un cuadrito.
        // Por ahora:
        // - no se mueve
        // - no crece
        // - solo representa una celda del grid
        DrawRectangle(
            posicionX,
            posicionY,
            tamano_de_celda,
            tamano_de_celda,
            RED
        );

        DrawRectangle(
            snake_food_position_x,
            snake_food_postion_y,
            tamano_de_celda,
            tamano_de_celda,
            GREEN
        );

        EndDrawing();
    }

    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}
