#pragma once
#include <raylib.h>
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
