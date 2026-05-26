#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "../graphics_operations.hpp"
using Vertices = std::vector<Vector2>;

class Polygon {
  public:

    // can later be calculated in this class directly
    virtual std::vector<Vector2> get_normals() const {
      std::vector<Vector2> normals{};
      normals.reserve(m_vertices.size());
        
      auto egdes_points = m_vertices;
      egdes_points.push_back(m_vertices.at(0));
      
      for (auto i{0}; i < (egdes_points.size() - 1); i++) {
        const auto edge = Vector2Subtract(m_vertices[i], m_vertices[i+1]);
        normals.push_back( calculate_normal(edge) );
      }

      return normals;
    }; 

    virtual Vertices get_vertices() const {
      return m_vertices;
    };  

  protected:
    Vertices m_vertices{};
};
#endif
