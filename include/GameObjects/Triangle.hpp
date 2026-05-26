#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../graphics_operations.hpp"
#include "Polygon.hpp"
#include <array>

class Triangle : public Polygon{
  
  public:
    Triangle(const Vector2& center, float side, const Color& color) : 
      m_center(center), m_color(color) , m_side(side){

      generate_corners(side);
    } 


    void draw() {
      DrawTriangleLines(m_vertices[0], m_vertices[1], m_vertices[2], m_color);
    }


    void translate(const Vector2& movement_force) {
      translate_point(m_center, movement_force);

      for (auto& corner : m_vertices) {
        translate_point(corner, movement_force);
      }
    }

    void rotate(float angle) {
      for (auto& corner : m_vertices) {
        rotate_point(corner, m_center, angle);
      }
    }

  protected:
    void generate_corners(float side) {
      m_vertices.reserve(3);
      m_vertices.push_back( Vector2Add(m_center, Vector2{-side, side}) );
      m_vertices.push_back( Vector2Add(m_center, Vector2{ side, side}) );
      m_vertices.push_back( Vector2Add(m_center, Vector2{ 0, -side })  );
    }


    float m_side {};

  public :
    Vector2 m_center {};
    Color m_color {};
};

#endif
