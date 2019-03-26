#pragma once
#include <memory>

class Bullet;

struct BulletDestroyed {
  std::shared_ptr<Bullet> bullet;
};