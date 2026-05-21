#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "raylib.h"
#include "raymath.h"

#include <vector>

class BulletManager {
  public:
    BulletManager(float default_bullet_speed, const Color& bullet_color) :
      m_bullet_speed(default_bullet_speed), m_bullet_color(bullet_color) {}


    void draw() {
      for (auto& bullet: m_bullets) {
        bullet.center = Vector2Add(
            bullet.center,
            Vector2Scale(bullet.direction , m_bullet_speed)
        );


        DrawCircleV(bullet.center, bullet.radius, m_bullet_color);
      }
    }

    void spawn_bullet(const Vector2& position, const Vector2& direction, float radius) {
      m_bullets.push_back(Bullet{position, direction, radius});
    }

  private:
    struct Bullet {
       Vector2 center;
       Vector2 direction;
       float radius;
    };


    std::vector<Bullet> m_bullets;
    Color m_bullet_color;
    float m_bullet_speed;
};


#endif

