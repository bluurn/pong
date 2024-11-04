#include <iostream>
#include <raylib.h>


struct Ball: Vector2 {
  Ball(float _x, float _y): Vector2{.x = _x, .y = _y } {}
  Ball(Vector2 pos): Vector2(pos) {}

  void draw() 
  {
    DrawCircleV(static_cast<Vector2>(*this), 20, WHITE);
  }
};


int main(int argc, char ** argv)
{
  Ball ball(100, 100);
  std::cout << "Hello Pong!" << std::endl;

  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(800, 600, "Pong");

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    ball.draw();
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}

