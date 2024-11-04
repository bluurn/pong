#include <raylib.h>
#include <raymath.h>

struct Paddle {
  Paddle(Vector2 _pos, Vector2 _size, float _speed)
      : pos(_pos), size(_size), speed(_speed) {}
  Vector2 pos;
  Vector2 size;
  float speed;

  void draw() { DrawRectangleV(pos, size, WHITE); }
  virtual void update() {}
};

struct Player : public Paddle {
public:
  Player(Vector2 _pos, Vector2 _size, float _speed)
      : Paddle(_pos, _size, _speed) {}

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

  void update(const Paddle &player, const Paddle &cpu) {
    if (pos.y + radius >= GetScreenHeight() || pos.y - radius <= 0) {
      speed.y *= -1;
    } else if (pos.x + radius >= GetScreenWidth() || pos.x - radius <= 0 ||
               CheckCollisionCircleRec(pos, radius,
                                       Rectangle{player.pos.x, player.pos.y,
                                                 player.size.x,
                                                 player.size.y}) ||
               CheckCollisionCircleRec(
                   pos, radius,
                   Rectangle{cpu.pos.x, cpu.pos.y, cpu.size.x, cpu.size.y})) {
      speed.x *= -1;
    }

    pos = Vector2Add(pos, speed);
  }
};

struct CPU : public Paddle {
  CPU(Vector2 _pos, Vector2 _size, float _speed)
      : Paddle(_pos, _size, _speed) {}

  void update(const Ball &ball) {
    if (ball.pos.y < pos.y) {
      pos.y -= speed;
    } else if (ball.pos.y > pos.y + size.y) {
      pos.y += speed;
    }

    if (pos.y <= 0)
      pos.y = 0;
    if (pos.y + size.y >= GetScreenHeight())
      pos.y = GetScreenHeight() - size.y;
  }
};

int main(int argc, char **argv) {
  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(1024, 800, "Pong");

  Ball ball(Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
            Vector2{5, 5}, 10);
  Player player(Vector2{50, 200}, Vector2{10, 200}, 5);
  CPU cpu(Vector2{GetScreenWidth() - 50.0f, 200}, Vector2{10, 200}, 5);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    player.draw();
    ball.draw();
    cpu.draw();

    player.update();
    ball.update(player, cpu);
    cpu.update(ball);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
