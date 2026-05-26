#ifndef  ASTEROIDS_H
#define  ASTEROIDS_H

#include "Triangle.hpp"
#include "raylib.h"
#include "raymath.h"
#include "../graphics_operations.hpp"

#include <algorithm>
#include <array>
#include <cstdlib>
#include "Triangle.hpp"

class Asteroid : public Triangle{
  public:
    enum class Size{
      SMALL = 1,
      MEDIUM = 2,
      BIG = 4
    };


    Asteroid (const Vector2& center, const Vector2& direction, float speed,  Size size, float rotation_step) :
      Triangle(center, center_distance(size), RAYWHITE),
      m_direction(direction),
      m_size(size),
      m_speed(speed), 
      m_rotation_intensity(rotation_step)   
    {};


      
    void move() {
      const Vector2&  movement_force = Vector2Scale(m_direction, m_speed);      
     
      this->translate(movement_force);
      this->rotate(m_rotation_intensity);
    }

    void shrink() {
      m_size = static_cast<Size>(
        static_cast<uint8_t>(m_size) / 2
      );
      
      m_vertices.clear();
      generate_corners(center_distance(m_size));
    } 

  private:
    
    float center_distance(Size asteroid_size) {
      return static_cast<int8_t>(asteroid_size) * 12.5;
    }



    Vector2 m_direction { -1, 1};

    Size m_size{};
    float m_speed{5};
    float m_rotation_intensity {};
};

#endif
