#include <raylib.h>
#include <raymath.h>
#include "constants.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "cpu.hpp"
#include "game.hpp"


int main(int argc, char **argv) {
  SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
  SetTargetFPS(60);
  InitWindow(SCREEN_W, SCREEN_H, "Pong");

  Player player(PLAYER_INIT_POS, PADDLE_SIZE, PLAYER_SPEED);
  CPU cpu(CPU_INIT_POS, PADDLE_SIZE, CPU_SPEED);
  Ball ball(SCREEN_CENTER, BALL_SPEED, BALL_RADIUS);

  Game game(player, cpu, ball);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    game.react();
    game.draw();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
