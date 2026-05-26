#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include "../../include/Timer.hpp"
#include "../../include/CollisionManager.hpp"
#include "Asteroids.hpp"
#include "BulletManager.hpp"

#include <atomic>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>


class AsteroidManager {
  public:
    Timer spawn_timer;

    static AsteroidManager* instance(float timer) {
      static AsteroidManager manager(timer);
      return &manager;
    }


    void draw() {
        for (auto& asteroid: m_asteroids) {
          asteroid.move();
          asteroid.draw();
        }
    }

    void handle_collsions(const BulletManager& bullet_manager) {
        for (auto& asteroid : m_asteroids) {
          for (auto& bullet : bullet_manager.m_bullets) {
            if (CollisionManager::are_colliding(asteroid, bullet) ) {
              asteroid.shrink();
            } 
          } 
        } 
    };

    void spawn_asteroid() {
      const auto spawn_circle_radius {
        std::max(
          SCREEN_HEIGHT / 2,
          SCREEN_WIDTH / 2
        )
      };

      const Vector2& spawn_position = random_asteroid_spawn_position(spawn_circle_radius);
      const Vector2& asteroid_direction = direction_from_to(spawn_position, random_center_deviation());

      m_asteroids.emplace_back(
          spawn_position,
          asteroid_direction,
          random_asteroid_speed(),
          random_asteroid_size(),
          (rand() % 10 + 1) * 0.01
      );
    }

  private:
    AsteroidManager(float spawn_time_lapse) :
      spawn_timer(spawn_time_lapse, FRAME_RATE) {
      
      spawn_timer.on_expiry([this]() {
       this->spawn_asteroid();
      }); 
    };



    Vector2 random_asteroid_spawn_position(uint32_t spawn_radius) {
      float angle = rand() % 360;
      Vector2 spawn_position{
        spawn_radius * cos(angle),
        spawn_radius * sin(angle)
      };

      return Vector2Add(spawn_position , Vector2{SCREEN_WIDTH/2., SCREEN_HEIGHT/2.});
    };

    Asteroid::Size random_asteroid_size() {
      uint8_t size_choice = rand() % 3;
      switch (size_choice) {
        case 0:  return Asteroid::Size::SMALL;
        case 1:  return Asteroid::Size::MEDIUM;
        case 2:  return Asteroid::Size::BIG;
      }

    };

    float random_asteroid_speed() {
      return std::max(static_cast<float>(rand() % 5), 0.7f); 
    }
  

    Vector2 random_center_deviation() {
      const Vector2 center{SCREEN_WIDTH/2. , SCREEN_HEIGHT/2.};
      
      const uint8_t deviation_factor = 3; 
      const float deviation_x =  rand() % (SCREEN_WIDTH / deviation_factor);
      const float deviation_y =  rand() % (SCREEN_HEIGHT /  deviation_factor); 
      const Vector2& deviated_center =  Vector2Add(center, Vector2{deviation_x, deviation_y});
        
      return deviated_center ;
    }


    Vector2 direction_from_to(const Vector2& spawn, const Vector2& point) {
      const Vector2& distance_from_center = Vector2Subtract(point, spawn);
      return Vector2Normalize(distance_from_center);
    }


    std::vector<Asteroid> m_asteroids {};
};


#endif

