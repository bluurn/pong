#include <raylib.h>
#include <raymath.h>

struct Ball: Vector2 {
  Ball(Vector2 _pos, Vector2 _speed, float _radius): pos(_pos), radius(_radius), speed(_speed) {}
  
  Vector2 pos;
  Vector2 speed;
  float radius;

  void draw() 
  {
    DrawCircleV(pos, radius, WHITE);
  }

  void update()
  {
    if(pos.y + radius >= GetScreenHeight() || pos.y - radius <= 0) {
      speed.y *= -1;
    } else if (pos.x + radius >= GetScreenWidth() || pos.x - radius <= 0) {
      speed.x *= -1;
    }

    pos = Vector2Add(pos, speed);
  }
};


int main(int argc, char ** argv)
{
  Ball ball(Vector2{100, 100}, Vector2{5, 5}, 20);

  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(1024, 800, "Pong");

  while(!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    ball.draw();
    ball.update();
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}

