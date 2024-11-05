#pragma once
#include <raylib.h>

struct Paddle {
  Vector2 pos;
  Vector2 size;
  float speed;
  int score;

  Paddle(Vector2 _pos, Vector2 _size, float _speed);

  void draw();
  virtual void update();
};
