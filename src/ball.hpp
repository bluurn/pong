#pragma once
#include "paddle.hpp"
#include "raylib.h"

struct Ball {
  Vector2 pos;
  Vector2 speed;
  float radius;

  Ball(Vector2 _pos, Vector2 _speed, float _radius);

  void draw();
  void update(const Paddle &player, const Paddle &cpu);
};
