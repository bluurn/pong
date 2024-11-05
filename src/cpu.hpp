#pragma once
#include "ball.hpp"
#include "paddle.hpp"

struct CPU : public Paddle {
  CPU(Vector2 _pos, Vector2 _size, float _speed);
  void update(const Ball &ball);
};
