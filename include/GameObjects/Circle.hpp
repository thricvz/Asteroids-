#ifndef CIRCLE_H
#define CIRCLE_H

#include "Polygon.hpp"
#include "raymath.h"
#include "raylib.h"

#include <cstdint>

struct Circle : Polygon{
    Circle(const Vector2& _center, float _radius) 
      : center{_center},
        radius{_radius} {
      
      generate_vertices(12);

    }
   


    void translate(const Vector2& movement_force) {
      translate_point(center, movement_force);

      for (auto& vertex : m_vertices) {
        translate_point(vertex, movement_force);
      }
    }


   Vector2 center;
   float radius;
   Polygon::m_vertices;
 
  private:
    void generate_vertices(uint8_t n_points) {
      m_vertices.reserve(n_points);
      float angle_step_radians {360.f/ n_points};
  
      
      for (auto i{0}; i < n_points; i++) {
        float angle = angle_step_radians * i;
        Vector2 vertex = Vector2{cos(angle) * radius, sin(angle) * radius};
        translate_point(vertex, center);

        m_vertices.push_back(vertex);
      };
    }
};
#endif
