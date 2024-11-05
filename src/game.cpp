#include "game.hpp"
#include "constants.hpp"

Game::Game(Paddle &_player, CPU &_cpu, Ball &_ball)
    : player(_player), cpu(_cpu), ball(_ball), state(State::INIT) {}

void Game::react() {
  if (IsKeyPressed(KEY_P))
    state = State::PAUSED;

  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
    state = State::PLAY;

  if (state != State::PLAY)
    return;

  checkWinConditions();
  player.update();
  ball.update(player, cpu);
  cpu.update(ball);
}

void Game::draw() {
  player.draw();
  ball.draw();
  cpu.draw();
  drawPlayerScore();
  drawCPUScore();
  drawHint();
}

void Game::reset() {
  ball.speed.x *= -1;
  ball.pos = BALL_INIT_POS;
  player.pos = PLAYER_INIT_POS;
  cpu.pos = CPU_INIT_POS;
}

void Game::checkWinConditions() {
  if (ball.pos.x + ball.radius >= SCREEN_W) {
    player.score++;
    state = State::PLAYER_WON;
    reset();
  } else if (ball.pos.x - ball.radius <= 0) {
    cpu.score++;
    state = State::CPU_WON;
    reset();
  }
}

void Game::drawPlayerScore() {
  DrawText(TextFormat("%d", player.score), FONT_SIZE, FONT_SIZE, FONT_SIZE,
           LIGHTGRAY);
}

void Game::drawCPUScore() {
  DrawText(TextFormat("%d", cpu.score), SCREEN_W - FONT_SIZE, FONT_SIZE,
           FONT_SIZE, LIGHTGRAY);
}

void Game::drawHint() {
  switch (state) {

  case State::INIT: {
    DrawText("Welcome! Use arrows to move paddle", SCREEN_W / 2,
             SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
    break;
  }
  case State::PAUSED: {
    DrawText("Paused! Move paddle to play", SCREEN_W / 2,
             SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
    break;
  }
  case State::PLAYER_WON: {
    DrawText("You won! Move paddle to play", SCREEN_W / 2,
             SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
    break;
  }
  case State::CPU_WON: {
    DrawText("CPU won! Move paddle to play", SCREEN_W / 2,
             SCREEN_H - 2 * FONT_SIZE, FONT_SIZE, DARKGRAY);
    break;
  }
  case State::PLAY:
    break;
  }
}
