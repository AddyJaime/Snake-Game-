#include <iostream>
#include <raylib.h>
using namespace std;

int main()
{
  // Window  initialization
  const int screen_width = 750;
  const int screen_height = 750;
  InitWindow(screen_width, screen_height, "Snake_Game");
  
  // set the target frame rate
  SetTargetFPS(60);

  // main game loop
  while (!WindowShouldClose)
  {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;

}