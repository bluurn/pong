#include "ball.hpp"
#include "constants.hpp"
#include "raymath.h"

Ball::Ball(Vector2 _pos, Vector2 _speed, float _radius)
    : pos(_pos), radius(_radius), speed(_speed) {}

void Ball::draw() { DrawCircleV(pos, radius, WHITE); }

void Ball::update(const Paddle &player, const Paddle &cpu) {
  if (pos.y + radius >= SCREEN_H || pos.y - radius <= 0) {
    speed.y *= -1;
  } else if (CheckCollisionCircleRec(pos, radius,
                                     Rectangle{player.pos.x, player.pos.y,
                                               player.size.x, player.size.y}) ||
             CheckCollisionCircleRec(
                 pos, radius,
                 Rectangle{cpu.pos.x, cpu.pos.y, cpu.size.x, cpu.size.y})) {
    speed.x *= -1;
  }

  pos = Vector2Add(pos, speed);
}
