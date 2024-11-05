#include "cpu.hpp"
#include "constants.hpp"

CPU::CPU(Vector2 _pos, Vector2 _size, float _speed)
    : Paddle(_pos, _size, _speed) {}

void CPU::update(const Ball &ball) {
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

