#include "player.hpp"
#include "constants.hpp"

void Player::update() {
  if (IsKeyUp(KEY_DOWN))
    pos.y -= speed;
  if (IsKeyUp(KEY_UP))
    pos.y += speed;
  if (pos.y <= 0)
    pos.y = 0;
  if (pos.y + size.y >= SCREEN_H)
    pos.y = SCREEN_H - size.y;
}

Player::Player(Vector2 _pos, Vector2 _size, float _speed)
    : Paddle(_pos, _size, _speed) {}
