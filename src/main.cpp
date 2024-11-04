#include <raylib.h>
#include <raymath.h>
struct Paddle {
  Paddle(Vector2 _pos, Vector2 _size, float _speed)
      : pos(_pos), size(_size), speed(_speed) {}

  Vector2 pos;
  Vector2 size;
  float speed;

  void draw() { DrawRectangleV(pos, size, WHITE); }

  void update() {
    if (IsKeyUp(KEY_DOWN))
      pos.y -= speed;
    if (IsKeyUp(KEY_UP))
      pos.y += speed;

    if (pos.y <= 0)
      pos.y = 0;
    if (pos.y + size.y >= GetScreenHeight())
      pos.y = GetScreenHeight() - size.y;
  }
};

struct Ball {
  Ball(Vector2 _pos, Vector2 _speed, float _radius)
      : pos(_pos), radius(_radius), speed(_speed) {}

  Vector2 pos;
  Vector2 speed;
  float radius;

  void draw() { DrawCircleV(pos, radius, WHITE); }

  void update(const Paddle &player) {
    if (pos.y + radius >= GetScreenHeight() || pos.y - radius <= 0) {
      speed.y *= -1;
    } else if (pos.x + radius >= GetScreenWidth() || pos.x - radius <= 0 ||
               CheckCollisionCircleRec(pos, radius,
                                       Rectangle{player.pos.x, player.pos.y,
                                                 player.size.x,
                                                 player.size.y})) {
      speed.x *= -1;
    }

    pos = Vector2Add(pos, speed);
  }
};

int main(int argc, char **argv) {
  Ball ball(Vector2{100, 100}, Vector2{5, 5}, 20);
  Paddle player(Vector2{10, 200}, Vector2{10, 200}, 20);

  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(1024, 800, "Pong");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    player.draw();
    player.update();

    ball.draw();
    ball.update(player);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
