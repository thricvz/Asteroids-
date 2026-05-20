#ifndef  ASTEROIDS_H
#define  ASTEROIDS_H

#include "raylib.h"
#include "raymath.h"
#include "../graphics_operations.hpp"

#include <algorithm>
#include <array>
#include <cstdlib>

class Asteroid {
  public:
    enum class Size{
      SMALL = 1,
      MEDIUM = 2,
      BIG = 4
    };


    Asteroid (const Vector2& center, const Vector2& direction, float speed,  Size size, float rotation_step) :
      m_center(center),
      m_direction(direction),
      m_size(size),
      m_speed(speed), 
      m_rotation_intensity(rotation_step)   
    {

      generate_corners();
    };


      
    void move() {
      const Vector2&  movement_force = Vector2Scale(m_direction, m_speed);      
      
      translate_point(m_center, movement_force);

      for (auto& corner : m_corners) {
        translate_point(corner, movement_force);
      }

      for (auto& corner : m_corners) {
        rotate_point(corner, m_center, m_rotation_intensity);
      }
    }

    void spawn() {};
    
    void draw() {
      DrawTriangleLines(m_corners[0], m_corners[1], m_corners[2], RAYWHITE);
    }

  private:

    void generate_corners() {
      float  side = center_distance(m_size);
      
      m_corners[0] = Vector2Add(m_center, Vector2{-side, side});
      m_corners[1] = Vector2Add(m_center, Vector2{ side, side});
      m_corners[2] = Vector2Add(m_center, Vector2{ 0, -side });
    }
    
    float center_distance(Size asteroid_size) {
      return static_cast<int8_t>(asteroid_size) * 12.5;
    }



    Vector2 m_center {};
    Vector2 m_direction { -1, 1};
    std::array<Vector2, 3> m_corners {};

    Size m_size{};
    float m_speed{5};
    float m_rotation_intensity {};
};

#endif
