#include "paddle.hpp"

Paddle::Paddle(Vector2 _pos, Vector2 _size, float _speed)
    : pos(_pos), size(_size), speed(_speed), score(0) {}

void Paddle::draw() { DrawRectangleV(pos, size, WHITE); }

void Paddle::update() {}
