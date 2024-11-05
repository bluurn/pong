#pragma once
#include "paddle.hpp"
struct Player : public Paddle {
public:
  Player(Vector2 _pos, Vector2 _size, float _speed);
  void update();
};
