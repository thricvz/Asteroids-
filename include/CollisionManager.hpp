#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../include/GameObjects/BulletManager.hpp"
#include "../include/GameObjects/Triangle.hpp"
#include "../include/GameObjects/Polygon.hpp"
#include <algorithm>
#include <complex>

struct Circle;

class CollisionManager {
  public:

    static bool are_colliding(const Polygon& p1, const Polygon& p2) {
      return SeparatingAxisTheorem::colliding(p1, p2);

    };
  
  private:
    class SeparatingAxisTheorem {
      public:
        static std::vector<float> project_vertices_on(const Vertices& vertices, const Vector2& line) {
          std::vector<float> projections;
          projections.reserve(vertices.size());

          for (const auto& vertex : vertices) 
            projections.push_back(Vector2DotProduct(vertex, line));
          
          return projections;
        }
        
        static bool colliding(const Polygon& p1, const Polygon& p2) {
          // concatenate all normals
          auto all_normals = p1.get_normals();
          const auto& p2_normals = p2.get_normals();
          all_normals.insert(all_normals.end(), p2_normals.begin(), p2_normals.end());
          
          for (const auto& axis: all_normals) {
            const auto& p1_projections = project_vertices_on(p1.get_vertices(), axis);
            const auto& p2_projections = project_vertices_on(p2.get_vertices(), axis);

            const auto max_p1 = std::max_element(p1_projections.begin(), p1_projections.end()) ;
            const auto min_p1 = std::min_element(p1_projections.begin(), p1_projections.end()) ;

            const auto max_p2 = std::max_element(p2_projections.begin(), p2_projections.end()) ;
            const auto min_p2 = std::min_element(p2_projections.begin(), p2_projections.end()) ;

            if ((*max_p1 < *min_p2) || (*max_p2 < *min_p1)) 
              return false;
          }

          return true;
        }

    };
};
#endif
