#include <raylib.h>
#include <iostream>

using namespace std;

// =================================================
// ENUM: Direcciones posibles del Snake
// =================================================
enum Direccion
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// =================================================
// STRUCT: Coordenadas en CELDAS (lógica del juego)
// =================================================
struct Coordenadas
{
    int x;
    int y;
};

struct  Coordenada_Comida
{
    int comida_posicion_x;
    int comida_posicion_y;
};


int main()
{
    // =================================================
    // CONFIGURACIÓN DEL GRID (REGLAS DEL MUNDO)
    // =================================================
    const int TAMANO_CELDA = 25;      // 1 celda = 25 píxeles
    const int CANTIDAD_CELDAS = 30;   // grid 30x30

    // =================================================
    // INICIALIZACIÓN DE LA VENTANA
    // =================================================
    InitWindow(
        TAMANO_CELDA * CANTIDAD_CELDAS,
        TAMANO_CELDA * CANTIDAD_CELDAS,
        "Snake Game - Grid Correcto"
    );

    SetTargetFPS(60);

    // =================================================
    // ESTADO INICIAL DEL SNAKE (CELDAS, NO PÍXELES)
    // =================================================
    Coordenadas snake = {3, 4};   // posición inicial en el grid
    Direccion direccion = RIGHT; // dirección inicial

    Coordenada_Comida comida = {5,7};

    // =================================================
    // CONTROL DE TIEMPO (MOVIMIENTO POR TICKS)
    // =================================================
    double ultimoMovimiento = GetTime(); // última vez que se movió
    double delayMovimiento = 0.5;        // cada cuántos segundos se mueve

    // =================================================
    // GAME LOOP PRINCIPAL
    // =================================================
    while (!WindowShouldClose())
    {
        // =============================================
        // 1️⃣ INPUT (CAMBIAR DIRECCIÓN)
        // =============================================
        if (IsKeyDown(KEY_RIGHT) && direccion != LEFT)
            direccion = RIGHT;
        else if (IsKeyDown(KEY_LEFT) && direccion != RIGHT)
            direccion = LEFT;
        else if (IsKeyDown(KEY_UP) && direccion != DOWN)
            direccion = UP;
        else if (IsKeyDown(KEY_DOWN) && direccion != UP)
            direccion = DOWN;

        // =============================================
        // 2️⃣ TIEMPO + MOVIMIENTO (SOLO CELDAS)
        // =============================================
        double tiempoActual = GetTime();

        // ¿Ya pasó suficiente tiempo para moverse?
        if (tiempoActual - ultimoMovimiento >= delayMovimiento)
        {
            // Mover UNA celda según la dirección
            if (direccion == RIGHT)
            // de la posicion inical donde esta pasa un cuadrito a la vez o muevete un cuadrito a la vez
                snake.x += 1;
            else if (direccion == LEFT)
                snake.x -= 1;
            else if (direccion == UP)
                snake.y -= 1;
            else if (direccion == DOWN)
                snake.y += 1;

            // Guardamos cuándo fue el último movimiento
            // sin esta linea no vamso a poder saber cual fue el ultimo movimiento que anotamos 
            ultimoMovimiento = tiempoActual;
        }
        
              if (snake.x < 0 || snake.x >= CANTIDAD_CELDAS || snake.y < 0 || snake.y >= CANTIDAD_CELDAS)
        {
            cout << "El snake se salio del grid" << "\n";
            break;
        }
         

        // =============================================
        // 3️⃣ CONVERSIÓN A PÍXELES (SOLO PARA DIBUJAR)
            // La pantalla NO entiende celdas
            // La pantalla SOLO entiende píxeles
            // por esa razon aqui se toma la poscion d eesa celda y se multiplica por el tamono y asi nos da la posicion 
            // en pantallad del cuadirto que es pixles 
        // =============================================
        int pixelX = snake.x * TAMANO_CELDA;
        int pixelY = snake.y * TAMANO_CELDA;

        int pixel_comida_x = comida.comida_posicion_x * TAMANO_CELDA;
        int pixel_comida_y = comida.comida_posicion_y * TAMANO_CELDA;

        // =============================================
        // 4️⃣ DIBUJO
        // =============================================
        BeginDrawing();
        ClearBackground(BLACK);

        // Dibujamos el snake
        DrawRectangle(
            pixelX,
            pixelY,
            TAMANO_CELDA,
            TAMANO_CELDA,
            RED
        );

        DrawRectangle(
            pixel_comida_x,
            pixel_comida_y ,
            TAMANO_CELDA,
            TAMANO_CELDA,
            GREEN
            
        );

        EndDrawing();
    }

    // =================================================
    // CERRAR JUEGO
    // =================================================
    CloseWindow();
    return 0;
}
