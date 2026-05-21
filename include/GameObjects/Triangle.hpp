#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../graphics_operations.hpp"
#include <array>

class Triangle {
  
  public:
    Triangle(const Vector2& center, float side, const Color& color) : 
      m_center(center), m_color(color) , m_side(side){

      generate_corners(side);
    } 


    void draw() {
      DrawTriangleLines(m_corners[0], m_corners[1], m_corners[2], m_color);
    }


    void translate(const Vector2& movement_force) {
      translate_point(m_center, movement_force);

      for (auto& corner : m_corners) {
        translate_point(corner, movement_force);
      }
    }

    void rotate(float angle) {
      for (auto& corner : m_corners) {
        rotate_point(corner, m_center, angle);
      }
    }

  private:
    void generate_corners(float side) {
      
      m_corners[0] = Vector2Add(m_center, Vector2{-side, side});
      m_corners[1] = Vector2Add(m_center, Vector2{ side, side});
      m_corners[2] = Vector2Add(m_center, Vector2{ 0, -side });
    }


  protected:
    Vector2 m_center {};
    std::array<Vector2, 3> m_corners {};
    Color m_color {};
    float m_side {};
};

#endif
