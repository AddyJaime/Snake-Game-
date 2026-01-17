#include <raylib.h>
#include <vector>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

// =================================================
// CONFIGURACIÓN DEL GRID
// =================================================
const int TAMANO_CELDA = 25;
const int CANTIDAD_CELDAS = 30;

double last_update_time = 0;

// NO PUEDO MOVER EL SNAKE TODO EL TIEMPO, SOLO PUEDO MOVERLO CADA CIERTO TIEMPO
// ESTA FUNCION SE ENCARGA DE ESO 
bool eventTriggered(double interval)
{
 double current_time = GetTime();
 if (current_time - last_update_time >= interval)
 {
    last_update_time = current_time;
    
    return true;
 }
   return false;
 
}


// COLORS
Color green = {173,204,96,255};
Color dark_green = {43,51,24,255};
// La  clase encapsula el acceso a sus miembros
// Encapsular SÍ es: Decidir qué muestro y qué no”

class Snake{
    public:
 // deque (double-ended queue): es una estructura de datos que permite insertar y eliminar elementos por delante y por detrás.
   deque<Vector2> body = {Vector2{10,10}, Vector2{9,10}, Vector2{8,10}};





   Texture2D headUp;
   Texture2D headDown;
   Texture2D headLeft;
   Texture2D headRight;

  
  Snake()
  {
    // Lee el archivo del disco Lo guarda en la RAM NO se dibuja todavía
      Image imgUp =  LoadImage("src/assets/milo-up.png");
      Image imgDown =  LoadImage("src/assets/milo-down.png");
    Image imgLeft =  LoadImage("src/assets/mio-left.png");
    Image imgRight =  LoadImage("src/assets/milo-right.png");

// Copia la imagen a la GPU .La convierte en textura. YA se puede dibujar
// 🎮 Ahora la GPU puede usarlaz
   headUp = LoadTextureFromImage(imgUp);
   headDown = LoadTextureFromImage(imgDown);
   headLeft = LoadTextureFromImage(imgLeft);
   headRight = LoadTextureFromImage(imgRight);

//    Ya no la necesitamos La GPU ya tiene su copia
// Liberamos memoria (MUY importante)
// 🧹 Limpieza

   UnloadImage(imgUp);
   UnloadImage(imgDown);
   UnloadImage(imgLeft);
   UnloadImage(imgRight);
  }

  ~Snake()
  {
    // Le decimos a la GPU:
// “Ya no necesito esta textura, bórrala”
// Si NO lo haces: La GPU se llena El juego consume más memoria
// Bugs
// Crashes
// Malas prácticas
    UnloadTexture(headUp);
    UnloadTexture(headDown);
    UnloadTexture(headLeft);
    UnloadTexture(headRight);
  }

//    posicion inicial mueve hacia la derecha
// {1,0}derecha
// {-1,0}izquierda
// {0,-1}arriba
// {0, 1}abajo

   Vector2 direccion = {1,0};
    // 🔴 ESTA VARIABLE NO AGREGA NADA POR SÍ SOLA
    // Es SOLO UNA SEÑAL que dice:
    // “En el PRÓXIMO movimiento, el snake debe crecer”
   bool addSegment = false;

    void Draw()

    {
        for(int i = 0; i < body.size(); i++){
            if (i == 0)
            {
            Texture2D head = headRight; //DEFAULT
            
            if (direccion.x == -1) head = headLeft;
            if (direccion.y == -1) head = headUp;
            if (direccion.y == 1) head = headDown;

            DrawTexture(
                head,
                body[i].x * TAMANO_CELDA,
                body[i].y * TAMANO_CELDA,
                WHITE

            );
            
           
            } else {

                float x = body[i].x  ;
                float y = body[i].y ;
                Rectangle segment = Rectangle{x *TAMANO_CELDA, y *TAMANO_CELDA,TAMANO_CELDA, TAMANO_CELDA };
                DrawRectangleRounded(segment,0.5, 6, dark_green);

            }
            


        };
    };
    // aqui se va a lograr el movimiento de la serpiente, quitando y metiendo 
    void Update()
    {
        // direccion Es hacia dónde te mueves
        // body[0] Es la posición ACTUAL de la cabeza
        // Vector2Add(a, b) Suma dos posiciones
        // El snake se mueve quitando la cola y agregando una nueva cabeza adelante.
        // this will move the snake's head in the direcion specified by the direction attribute
        // esta linea estaba dentro del if y el else pero la saque y ahora esta afuera
        // 👉 Si una línea se ejecuta SIEMPRE, no debe estar dentro de un if/else.
        // el snake siempre se mueve osea siempre hay que agregar una cabeza se mueva o no 
        body.push_front(Vector2Add(body[0], direccion));


            // 👉 Si addSegment es true:
            // NO quitamos la cola
            // Solo agregamos una nueva cabeza
            // Resultado: el snake CRECE en 1 segment
        if(addSegment){
            
            // Ya cumplimos la orden de crecer,
            // así que volvemos la señal a false
            addSegment = false;
        } else
        {
            body.pop_back();
          
        }
    }

    void Reset()
    {
        body = {Vector2{6,10}, Vector2{5,10}, Vector2{4,10}};
        direccion = {1,0};
    }

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

class Game {
    public:
        Food comida = Food();
        Snake snake = Snake();
        bool running = true;
        int score = 0;
        


        void Draw()
        {
            comida.Draw();
            snake.Draw();
        }

        void Update()
        {
            if (running)
            {
                CheckCollisionWithFood();
                CheckCollisionWithEdge();   
                CheckCollisionWithTail();
                snake.Update();
            }
        }

        void CheckCollisionWithFood()
        {
            if(Vector2Equals(snake.body[0], comida.position)){
                
                comida.position = comida.GenerateRandonPos();
                // En el próximo movimiento, crecer, es solo una nota
                // aqui decetamos la colision para poder agregar un segment 
                snake.addSegment = true;     
                score += 1;           
            }
        }
        
        void CheckCollisionWithEdge()
        {
          
            if (snake.body[0].x == CANTIDAD_CELDAS || snake.body[0].x == -1)
            { 
                GameOver();     
            }

            if (snake.body[0].y == CANTIDAD_CELDAS || snake.body[0].y == -1)
            {
                GameOver();
                          
            }
            
        }

        void GameOver()
        {
           snake.Reset();
           running = false;
           ResetScore();
        }

        void ResetScore()
        {
            score = 0;
        }

        void  CheckCollisionWithTail()
        {
            for (int i = 1; i < snake.body.size(); i++)
            {
                
                if (Vector2Equals(snake.body[0], snake.body[i]))
                {
                    GameOver();
                    return; 
                }
            
            }
            
        }


};

int main()
{
    InitWindow(
        TAMANO_CELDA * CANTIDAD_CELDAS,
        TAMANO_CELDA * CANTIDAD_CELDAS,
        "Milo Game"
    );

    SetTargetFPS(60);

    Game game = Game();


    // =================================================
    // GAME LOOP
    // =================================================
    while (!WindowShouldClose())
    {

        //cuando el juego este detenido 
        // el jugador puede presiona la tecla R para empezar de nuevo
        if(!game.running){
             if (IsKeyPressed(KEY_R))
             {
                game.snake.Reset();
                game.running  = true;
                last_update_time = GetTime();
             }
             


        } 
        
        // SI EL JUEGO SI ESTA CORRIENDO, ENTONCES ESCUCHA LAS TECLAS NORMALES PARA MOVER LA SERPIENTE
        
        else {
            // -------------------------------------------------
            // INPUT (CAMBIO DE DIRECCIÓN)
            // -------------------------------------------------
            // si la direccion actual no es hacia abajo entonce puede subir
            if (IsKeyPressed(KEY_UP) && game.snake.direccion.y != 1)
            {
                // sube
                game.snake.direccion = {0,-1};
            }
            // si la direccion actual no es hacia arriba entonce puede bajar
            if(IsKeyPressed(KEY_DOWN) && game.snake.direccion.y != -1)
            {
                game.snake.direccion = {0, 1};
            }
    // Si se presiona la tecla izquierda y la dirección actual NO es hacia la derecha
            if(IsKeyPressed(KEY_LEFT) && game.snake.direccion.x != 1)
            {
                // mover hacia la izquierda
                game.snake.direccion = {-1, 0};
            }
    // si se presiona la tecla derecha y la direccion actual NO es hacia la derecha
            if (IsKeyPressed(KEY_RIGHT) && game.snake.direccion.x != -1)
            {
                // mover hacia la derecha
                game.snake.direccion = {1, 0};
            }
        

        }
     

        // -------------------------------------------------
        // DIBUJO
        // -------------------------------------------------
        BeginDrawing();

        if(eventTriggered(0.3) && game.running){
           game.Update();

        }


        ClearBackground(green);
        game.snake.Draw();
         game.comida.Draw();

          if (!game.running)
    {
        int textWidth = MeasureText("GAME OVER - Press R to Restart", 30);
        DrawText("GAME OVER - Press R to Restart", (GetScreenWidth() - textWidth)/2 , 200, 30, RED);
    }
    
     string text = "Score: " + to_string(game.score);
    //  c_str convierte el texto a lo que drawText entiende 
        DrawText(text.c_str(), 10, 10, 30,  DARKGRAY);
        
    


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
