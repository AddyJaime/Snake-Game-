#include <raylib.h>
#include <vector>
#include <iostream>

using namespace std;

// =================================================
// CONFIGURACIÓN DEL GRID
// =================================================
const int TAMANO_CELDA = 25;  
const int CANTIDAD_CELDAS = 30;

// =================================================
// ENUM DIRECCIÓN
// =================================================
enum Direccion
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// =================================================
// STRUCT COORDENADAS
// =================================================
struct Coordenadas
{
    int x;
    int y;
};

struct Coordenadas_comida
{
    int x_comida;
    int y_comida;
};

int main()
{
    // =================================================
    // VENTANA
    // =================================================
    InitWindow(
        TAMANO_CELDA * CANTIDAD_CELDAS,
        TAMANO_CELDA * CANTIDAD_CELDAS,
        "Snake Game"
    );

    SetTargetFPS(60);

    // =================================================
    // SNAKE = VECTOR DE COORDENADAS
    // =================================================
    vector<Coordenadas> snake;

    // Snake inicial (3 partes)
    snake.push_back({10, 10}); // cabeza
    snake.push_back({9, 10});  // cuerpo
    snake.push_back({8, 10});  // cola


    Coordenadas_comida comida = {4,6};

    Direccion direccion = RIGHT;

    // =================================================
    // TIEMPO DE MOVIMIENTO
    // =================================================
    double ultimoMovimiento = GetTime();
    double delayMovimiento = 0.3;

    bool is_snake_out = false;

    // =================================================
    // GAME LOOP
    // =================================================
    while (!WindowShouldClose())
    {
        // =============================================
        // INPUT (CAMBIAR DIRECCIÓN)
        // =============================================
        if (IsKeyPressed(KEY_RIGHT) && direccion != LEFT)
            direccion = RIGHT;
        if (IsKeyPressed(KEY_LEFT) && direccion != RIGHT)
            direccion = LEFT;
        if (IsKeyPressed(KEY_UP) && direccion != DOWN)
            direccion = UP;
        if (IsKeyPressed(KEY_DOWN) && direccion != UP)
            direccion = DOWN;

        // =============================================
        // MOVIMIENTO POR TIEMPO
        // =============================================
        double tiempoActual = GetTime();

        if (tiempoActual - ultimoMovimiento >= delayMovimiento && !is_snake_out)
        {
            // -----------------------------------------
            // 1️⃣ MOVER CUERPO (DE ATRÁS HACIA ADELANTE)
            // ESTUDIAR
            // -----------------------------------------

            // snake.size() - 1 apunta al ultimo indice que son 2
            // int i = snake.size() - 1 aqui signica que en i vamos a inicar con el ultimo elemento que seria 2
            // i > 0 = i siguie siendo mayor que 0, si si entra al loop 
            // Este loop hace que cada elemento copie al que está delante, empezando por el último.
                for (int i = snake.size() - 1; i > 0; i--)
            {
                // El cuadrito de atrás copia EXACTAMENTE la posición del cuadrito que está delante
                snake[i] = snake[i - 1];
            }

            // -----------------------------------------
            // 2️⃣ MOVER CABEZA
            // -----------------------------------------
            if (direccion == RIGHT) snake[0].x += 1;
            if (direccion == LEFT)  snake[0].x -= 1;
            if (direccion == UP)    snake[0].y -= 1;
            if (direccion == DOWN)  snake[0].y += 1;

            ultimoMovimiento = tiempoActual;

            
          if (snake[0].x == comida.x_comida && snake[0].y == comida.y_comida)
          {
            int randomX = GetRandomValue(0, CANTIDAD_CELDAS - 1);
            int randomY = GetRandomValue(0, CANTIDAD_CELDAS - 1);
            comida.x_comida = randomX;
            comida.y_comida  = randomY;
          }
          


            // -----------------------------------------
            // 3️⃣ LÍMITES DEL MAPA (SOLO CABEZA)
            // -----------------------------------------
            if (snake[0].x < 0 || snake[0].x >= CANTIDAD_CELDAS ||
                snake[0].y < 0 || snake[0].y >= CANTIDAD_CELDAS)
            {
                is_snake_out = true;
            }
            
            


        }

        // =============================================
        // DIBUJO
        // =============================================
        BeginDrawing();
        ClearBackground(BLACK);

        // ESTUDIAR
        // Dibujar todo el snake
        for (int i = 0; i < snake.size(); i++)
        {
            DrawRectangle(
                snake[i].x * TAMANO_CELDA,
                snake[i].y * TAMANO_CELDA,
                TAMANO_CELDA,
                TAMANO_CELDA,
                (i == 0) ? RED : GREEN // cabeza roja, cuerpo verde
            );
        }

        DrawRectangle(
            comida.x_comida * TAMANO_CELDA,
            comida.y_comida * TAMANO_CELDA,
            TAMANO_CELDA,
            TAMANO_CELDA,
            BLUE
        );

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
