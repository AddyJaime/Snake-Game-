#include <raylib.h>
#include <iostream>
#include <vector>

using namespace std;

// =================================================
// ENUM: DIRECCIÓN DEL SNAKE (ESTADO, NO MOVIMIENTO)
// =================================================
// Este enum define TODAS las direcciones posibles que el snake puede tener.
// Aquí NO se mueve el snake, solo se define HACIA DÓNDE está apuntando.
//
// Un enum es una lista CERRADA de opciones:
// - Solo existen las opciones que se escriben aquí.
// - No se pueden inventar direcciones nuevas.
//
// La dirección es el ESTADO del snake:
// - Presionar una tecla NO mueve al snake.
// - Presionar una tecla SOLO cambia este estado (la dirección).
//
// El movimiento del snake se hace en otra parte del código,
// usando la dirección que está guardada aquí.
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

// Dentro de esa cajita tú guardas datos que pertenecen a UNA sola cosa.
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
// El juego se maneja usando un GRID (cuadrícula).
// Trabajar en celdas es más fácil que trabajar directo en píxeles.
// Primero pensamos el juego en celdas (lógica),
// y luego convertimos esas celdas a píxeles para dibujar en pantalla.
// =================================================

const int TAMANO_CELDA = 25;      
// Tamaño de UNA celda en píxeles.
// Cada celda es un cuadrito de 30x30 píxeles.
// El snake se mueve de celda en celda, no de píxel en píxel.

const int CANTIDAD_CELDAS = 30;   
// Cantidad de celdas del grid.
// El tablero del juego es de 30 celdas de ancho y 30 de alto (30x30).




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
    // Coordenadas snake = {3, 4};   // posición inicial en el grid
    Direccion direccion = RIGHT; // dirección inicial

     // ===============================
    // 🐍 SNAKE = VECTOR DE COORDENADAS
    // ===============================

    vector<Coordenadas> snake;

    snake.push_back({10,10}); //cabeza
    snake.push_back({9,10}); // cuerpo
    snake.push_back({8, 10}); //cola

    Coordenada_Comida comida = {5,7};

    // =================================================
    // CONTROL DE TIEMPO (MOVIMIENTO POR TICKS)
    // =================================================
    double ultimoMovimiento = GetTime(); // última vez que se movió
    double delayMovimiento = 0.5;        // cada cuántos segundos se mueve

    bool is_snake_out = false;

    // =================================================
    // GAME LOOP PRINCIPAL
    // =================================================
    while (!WindowShouldClose())
    {
        // =============================================
        // 1️⃣ INPUT (CAMBIAR DIRECCIÓN) o Cambiar el estado 
        // trabajar con esto luego 
        // =============================================
        if (IsKeyDown(KEY_RIGHT))
            direccion = RIGHT;
        else if (IsKeyDown(KEY_LEFT))
            direccion = LEFT;
        else if (IsKeyDown(KEY_UP))
            direccion = UP;
        else if (IsKeyDown(KEY_DOWN))
            direccion = DOWN;

       // =============================================
// 2️⃣ TIEMPO + MOVIMIENTO (SOLO CELDAS)
// =============================================
// Este bloque controla CUÁNDO y CÓMO se mueve el snake.
// ❌ Aquí NO se lee el teclado
// ❌ Aquí NO se dibuja nada
// ✅ Aquí SOLO se decide el movimiento usando el tiempo y la dirección
// =============================================

// Obtenemos el tiempo actual del juego en segundos.
// GetTime() devuelve cuántos segundos han pasado desde que empezó el programa.
// Ejemplo: 0.0, 0.5, 1.2, 3.8, etc.
double tiempoActual = GetTime();


// Preguntamos:
// ¿Ya pasó suficiente tiempo desde el último movimiento?
// Esto evita que el snake se mueva en cada frame.
// El snake solo debe moverse cuando:
// tiempoActual - ultimoMovimiento >= delayMovimiento
if (tiempoActual - ultimoMovimiento >= delayMovimiento)
{
    // Verificamos si el snake todavía está dentro del tablero.
    // is_snake_out funciona como una bandera:
    // false = el snake sigue vivo
    // true  = el snake se salió del mundo
    if (!is_snake_out)
    {
        // ================================
        // MOVIMIENTO LÓGICO (EN CELDAS)
        // ================================
        // Aquí el snake se mueve UNA SOLA CELDA.
        // NO son píxeles.
        // snake.x y snake.y representan posiciones en el GRID.
        //
        // +1 o -1 significa:
        // "muévete un cuadrito en esa dirección"

        if (direccion == RIGHT)
            // Mover una celda a la derecha
            snake.x += 1;

        else if (direccion == LEFT)
            // Mover una celda a la izquierda
            snake.x -= 1;

        else if (direccion == UP)
            // Subir una celda (en pantalla subir = restar Y)
            snake.y -= 1;

        else if (direccion == DOWN)
            // Bajar una celda (en pantalla bajar = sumar Y)
            snake.y += 1;
    }

    // =============================================
    // ACTUALIZAMOS EL TIEMPO DEL ÚLTIMO MOVIMIENTO
    // =============================================
    // Esta línea es CRÍTICA.
    // Aquí guardamos el momento EXACTO en que el snake se movió.
    //
    // Sin esta línea:
    // - el programa pensaría que el snake nunca se movió
    // - la condición del tiempo siempre sería verdadera
    // - el snake se movería miles de veces por segundo (sale volando)
    ultimoMovimiento = tiempoActual;


    // =============================================
    // DETECCIÓN DE SALIDA DEL TABLERO (LÍMITES)
    // =============================================
    // Aquí verificamos si el snake se salió del grid.
    //
    // snake.x < 0                  → salió por la izquierda
    // snake.x >= CANTIDAD_CELDAS   → salió por la derecha
    // snake.y < 0                  → salió por arriba
    // snake.y >= CANTIDAD_CELDAS   → salió por abajo
    //
    // Si cualquiera de estas condiciones se cumple,
    // el snake ya no está dentro del mundo del juego.
    if (snake.x < 0 || snake.x >= CANTIDAD_CELDAS ||
        snake.y < 0 || snake.y >= CANTIDAD_CELDAS)
    {
        // Marcamos que el snake está fuera.
        // A partir de aquí:
        // - ya no se mueve
        // - el juego puede terminar o mostrar un mensaje
        is_snake_out = true;
    }
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
