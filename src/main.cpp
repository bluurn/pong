#include <raylib.h>
#include <raymath.h>

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int FONT_SIZE = 20;
const Vector2 PADDLE_SIZE{10, 150};
const int PLAYER_SPEED = 5;
const int CPU_SPEED = 4;
const Vector2 BALL_SPEED{6, 6};
const int BALL_RADIUS = 10;
const Vector2 PLAYER_INIT_POS{50, (SCREEN_H - PADDLE_SIZE.y) / 2};
const Vector2 CPU_INIT_POS{SCREEN_W - 50, (SCREEN_H - PADDLE_SIZE.y) / 2};
const Vector2 BALL_INIT_POS{SCREEN_W / 2.0f, SCREEN_H / 2.0f};

struct Paddle {
  Paddle(Vector2 _pos, Vector2 _size, float _speed)
      : pos(_pos), size(_size), speed(_speed), score(0) {}
  Vector2 pos;
  Vector2 size;
  float speed;
  int score;

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
    if (pos.y + size.y >= SCREEN_H)
      pos.y = SCREEN_H - size.y;
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
    if (pos.y + radius >= SCREEN_H || pos.y - radius <= 0) {
      speed.y *= -1;
    } else if (CheckCollisionCircleRec(pos, radius,
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
    if (pos.y + size.y >= SCREEN_H)
      pos.y = SCREEN_H - size.y;
  }
};

enum GameState {
  INIT,
  PAUSED,
  PLAYER_WON,
  CPU_WON,
  PLAY,
};

struct Game {
  Game(Paddle &_player, CPU &_cpu, Ball &_ball)
      : player(_player), cpu(_cpu), ball(_ball) {}

  Paddle &player;
  CPU &cpu;
  Ball &ball;
  GameState GameState = INIT;

  void draw() {
    player.draw();
    ball.draw();
    cpu.draw();
    drawPlayerScore();
    drawCPUScore();
    drawHint();
  }

  void react() {
    if (IsKeyPressed(KEY_P))
      GameState = PAUSED;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
      GameState = PLAY;

    if (GameState != PLAY)
      return;

    checkWinConditions();
    player.update();
    ball.update(player, cpu);
    cpu.update(ball);
  }

  void reset() {
    ball.speed.x *= -1;
    ball.pos = BALL_INIT_POS;
    player.pos = PLAYER_INIT_POS;
    cpu.pos = CPU_INIT_POS;
  }

  void checkWinConditions() {
    if (ball.pos.x + ball.radius >= SCREEN_W) {
      player.score++;
      GameState = PLAYER_WON;
      reset();
    } else if (ball.pos.x - ball.radius <= 0) {
      cpu.score++;
      GameState = CPU_WON;
      reset();
    }
  }

  void drawPlayerScore() {
    DrawText(TextFormat("%d", player.score), FONT_SIZE, FONT_SIZE, FONT_SIZE,
             LIGHTGRAY);
  }

  void drawCPUScore() {
    DrawText(TextFormat("%d", cpu.score), SCREEN_W - FONT_SIZE, FONT_SIZE,
             FONT_SIZE, LIGHTGRAY);
  }

  void drawHint() {
    switch (GameState) {

    case INIT: {
      DrawText("Welcome! Use arrows to move paddle", SCREEN_W / 2, SCREEN_H - 2 * FONT_SIZE,
               FONT_SIZE, DARKGRAY);
      break;
    }
    case PAUSED: {
      DrawText("Paused! Move paddle to play", SCREEN_W / 2, SCREEN_H - 2 * FONT_SIZE,
               FONT_SIZE, DARKGRAY);
      break;
    }
    case PLAYER_WON: {
      DrawText("You won! Move paddle to play", SCREEN_W / 2,
               SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
      break;
    }
    case CPU_WON: {
      DrawText("CPU won! Move paddle to play", SCREEN_W / 2,
               SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
      break;
    }
    case PLAY:
      break;
    }
  }
};

int main(int argc, char **argv) {
  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(SCREEN_W, SCREEN_H, "Pong");

  Player player(PLAYER_INIT_POS, PADDLE_SIZE, PLAYER_SPEED);
  CPU cpu(CPU_INIT_POS, PADDLE_SIZE, CPU_SPEED);
  Ball ball(BALL_INIT_POS, BALL_SPEED, BALL_RADIUS);

  Game game(player, cpu, ball);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    game.draw();
    EndDrawing();
    game.react();
  }

  CloseWindow();

  return 0;
}
