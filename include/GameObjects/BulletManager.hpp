#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "raylib.h"
#include "raymath.h"
#include "Circle.hpp"

#include <vector>

class AsteroidManager;

class BulletManager {
  friend AsteroidManager;
  public:
    BulletManager(float default_bullet_speed, const Color& bullet_color) :
      m_bullet_speed(default_bullet_speed), m_bullet_color(bullet_color) {}


    void draw() {
      for (auto& bullet: m_bullets) {
        bullet.translate(Vector2Scale(bullet.direction , m_bullet_speed));

        DrawCircleV(bullet.center, bullet.radius, m_bullet_color);
      }
    }

    void spawn_bullet(const Vector2& position, const Vector2& direction, float radius) {
      m_bullets.emplace_back(position, radius, direction);
    }

    void clean_up() {
      auto delete_start = std::remove_if(m_bullets.begin(), m_bullets.end(), 
          [](const Bullet& bullet){
            return bullet.should_be_destroyed();
      });
    
      m_bullets.erase(delete_start, m_bullets.end());
      
    }

  private:
    struct Bullet : Circle{
       Bullet(const Vector2& _position, float radius, const Vector2& _direction) 
         : direction(_direction),
          Circle(_position, radius) {};
       Vector2 direction;

      bool should_be_destroyed() const {
        return has_collided || out_of_bounds(); 
      } 
      bool has_collided {false};
    };


    std::vector<Bullet> m_bullets;
    Color m_bullet_color;
    float m_bullet_speed;
};


#endif

