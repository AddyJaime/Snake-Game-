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
// DIRECCIÓN DEL SNAKE
// =================================================
enum Direccion
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// =================================================
// ESTRUCTURAS
// =================================================
struct Coordenadas
{
    int x;
    int y;
};

// COLORS
Color green = {173,204,96,255};
Color dark_green = {43,51,24,255};
// La  clase encapsula el acceso a sus miembros
// Encapsular SÍ es: Decidir qué muestro y qué no”
class Food {
    public:
    Vector2 position = {5,6};
    // Texture2D viene de raylib porque c++ no sabe nada de imagen
    // Raylib es la que le enseña a C++ a dibujar cosas.
    // texture2d es una imagen que ya fue enviada a la GPU
    Texture2D texture;

    // Constructor
    Food(){
        // “Abre el archivo y ponlo en RAM”
        Image image = LoadImage("src/assets/16_burger_dish.png");
        // “Cópialo a la GPU para poder dibujarlo”
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Food(){
        UnloadTexture(texture);
    }
    void Draw(){
       DrawTexture(texture, position.x *  TAMANO_CELDA, position.y *  TAMANO_CELDA, WHITE);
    };
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

    // FOOD
    Food comida = Food();

    // =================================================
    // SNAKE (VECTOR DE COORDENADAS)
    // =================================================
    vector<Coordenadas> snake;

    // Snake inicial (3 partes)
    snake.push_back({10, 10}); // cabeza
    snake.push_back({9, 10});  // cuerpo
    snake.push_back({8, 10});  // cola

    // =================================================
    // COMIDA
    // =================================================
    // CoordenadasComida comida = {4, 6};

    // =================================================
    // ESTADO DEL JUEGO
    // =================================================
    Direccion direccion = RIGHT;
    bool is_snake_out = false;

    // =================================================
    // CONTROL DE TIEMPO
    // =================================================
    double ultimoMovimiento = GetTime();
    double delayMovimiento = 0.3;

    // =================================================
    // GAME LOOP
    // =================================================
    while (!WindowShouldClose())
    {
        // -------------------------------------------------
        // INPUT (CAMBIO DE DIRECCIÓN)
        // -------------------------------------------------
        if (IsKeyPressed(KEY_RIGHT) && direccion != LEFT)  direccion = RIGHT;
        if (IsKeyPressed(KEY_LEFT)  && direccion != RIGHT) direccion = LEFT;
        if (IsKeyPressed(KEY_UP)    && direccion != DOWN)  direccion = UP;
        if (IsKeyPressed(KEY_DOWN)  && direccion != UP)    direccion = DOWN;

        // -------------------------------------------------
        // MOVIMIENTO CONTROLADO POR TIEMPO
        // -------------------------------------------------
        double tiempoActual = GetTime();

        if (tiempoActual - ultimoMovimiento >= delayMovimiento && !is_snake_out)
        {
            // 1️⃣ MOVER CUERPO (DE ATRÁS HACIA ADELANTE)
            for (int i = snake.size() - 1; i > 0; i--)
            {
                snake[i] = snake[i - 1];
            }

            // 2️⃣ MOVER CABEZA
            if (direccion == RIGHT) snake[0].x += 1;
            if (direccion == LEFT)  snake[0].x -= 1;
            if (direccion == UP)    snake[0].y -= 1;
            if (direccion == DOWN)  snake[0].y += 1;

            ultimoMovimiento = tiempoActual;

            // 3️⃣ COMER COMIDA
            if (snake[0].x == comida.position.x && snake[0].y == comida.position.y)
            {
                comida.position.x = GetRandomValue(0, CANTIDAD_CELDAS - 1);
                comida.position.y = GetRandomValue(0, CANTIDAD_CELDAS - 1);

                // Crecer el snake
                snake.push_back(snake.back());
            }

            // 4️⃣ LÍMITES DEL MAPA
            if (snake[0].x < 0 || snake[0].x >= CANTIDAD_CELDAS ||
                snake[0].y < 0 || snake[0].y >= CANTIDAD_CELDAS)
            {
                is_snake_out = true;
            }
        }

        // -------------------------------------------------
        // DIBUJO
        // -------------------------------------------------
        BeginDrawing();
        ClearBackground(green);

        // Dibujar snake completo
        for (int i = 0; i < snake.size(); i++)
        {
                DrawRectangle(
                        snake[i].x * TAMANO_CELDA,
                        snake[i].y * TAMANO_CELDA,
                        TAMANO_CELDA,
                        TAMANO_CELDA,
                        (i == 0) ? RED : GREEN
                    );
                }
                
                comida.Draw();
        // // Dibujar comida
        // DrawRectangle(
        //     comida.x * TAMANO_CELDA,
        //     comida.y * TAMANO_CELDA,
        //     TAMANO_CELDA,
        //     TAMANO_CELDA,
        //     GREEN
        // );

        EndDrawing(); 
    }

    CloseWindow();
    return 0;
}
