#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <algorithm>
#include "../graphics_operations.hpp"
using Vertices = std::vector<Vector2>;

class Polygon {
  public:
    Polygon() = default;
    virtual ~Polygon() = default;
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

    virtual bool out_of_bounds() const {
      // all edges are out of the area of the screen 
      return std::all_of(m_vertices.begin(), m_vertices.end(), 
          [](const Vector2& vertex) {
            return is_out_of_bounds(vertex, SPAWN_MARGIN);
          }
      );
    }

  protected:
    Vertices m_vertices{};
};
#endif
