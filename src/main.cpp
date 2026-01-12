#include <raylib.h>
#include <vector>
#include <iostream>
#include <deque>

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

class Snake{
    public:
    deque<Vector2> body = {Vector2{10,10}, Vector2{9,10}, Vector2{8,10}};

    void Draw()
    {
        for(int i = 0; i < body.size(); i++){
            int x = body[i].x ;
            int y = body[i].y ;
            DrawRectangle(x * TAMANO_CELDA, y * TAMANO_CELDA, TAMANO_CELDA, TAMANO_CELDA, dark_green);

        };
    };

};


class Food {
    public:
    Vector2 position;
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

        // esta funcion se esta llamando desde abajo para cambiar la posicon de la comida 
        position = GenerateRandonPos();
    }

    ~Food(){
        UnloadTexture(texture);
    }
    void Draw(){
       DrawTexture(texture, position.x *  TAMANO_CELDA, position.y *  TAMANO_CELDA, WHITE);
    };

    Vector2 GenerateRandonPos(){
        float x = GetRandomValue(0, CANTIDAD_CELDAS - 1);
        float y = GetRandomValue(0, CANTIDAD_CELDAS - 1);
        return Vector2{x, y};
    }

    
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
    Snake snake = Snake();

    // =================================================
    // SNAKE (VECTOR DE COORDENADAS)
    // =================================================
    // vector<Coordenadas> snake;

    // Snake inicial (3 partes)


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
            for (int i = snake.body.size() - 1; i > 0; i--)
            {
                snake.body[i] = snake.body[i - 1];
            }

            // 2️⃣ MOVER CABEZA
            if (direccion == RIGHT) snake.body[0].x += 1;
            if (direccion == LEFT)  snake.body[0].x -= 1;
            if (direccion == UP)    snake.body[0].y -= 1;
            if (direccion == DOWN)  snake.body[0].y += 1;

            ultimoMovimiento = tiempoActual;

            // 3️⃣ COMER COMIDA
            if (snake.body[0].x == comida.position.x && snake.body[0].y == comida.position.y)
            {
                comida.position.x = GetRandomValue(0, CANTIDAD_CELDAS - 1);
                comida.position.y = GetRandomValue(0, CANTIDAD_CELDAS - 1);

                // Crecer el snake
                snake.body.push_back(snake.body.back());
            }

            // 4️⃣ LÍMITES DEL MAPA
            if (snake.body[0].x < 0 || snake.body[0].x >= CANTIDAD_CELDAS ||
                snake.body[0].y < 0 || snake.body[0].y >= CANTIDAD_CELDAS)
            {
                is_snake_out = true;
            }
        }

        // -------------------------------------------------
        // DIBUJO
        // -------------------------------------------------
        BeginDrawing();
        ClearBackground(green);
        snake.Draw();
         comida.Draw();


        EndDrawing(); 
    }

    CloseWindow();
    return 0;
}
