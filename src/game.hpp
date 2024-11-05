#pragma once
#include "cpu.hpp"
#include "paddle.hpp"

struct Game {
  enum struct State {
    INIT = 0,
    PAUSED,
    PLAYER_WON,
    CPU_WON,
    PLAY,
  };

  Game(Paddle &_player, CPU &_cpu, Ball &_ball);

  Paddle &player;
  CPU &cpu;
  Ball &ball;
  State state;

  void draw();
  void react();
  void reset();
  void checkWinConditions();
  void drawPlayerScore();
  void drawCPUScore();
  void drawHint();
  void drawLineInTheMiddle();
  void drawCircleInTheMiddle();
};
