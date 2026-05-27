#include "include/graphics_operations.hpp"
#include <cmath>

void rotate_point(Vector2& point, const Vector2& origin, float angle) {
  
  float x_at_origin = (point.x - origin.x);
  float y_at_origin = (point.y - origin.y);

  point.x = origin.x + x_at_origin * cos(angle) - y_at_origin * sin(angle);
  point.y = origin.y + x_at_origin * sin(angle) + y_at_origin * cos(angle);

}

void translate_point(Vector2& point, const Vector2& force) {
  point = Vector2Add(point, force);

};

Vector2 calculate_normal(const Vector2& side) {
  return {side.y, -side.x};
}

bool is_out_of_bounds(const Vector2& position, int32_t margin) {
  return (position.x < (0 - margin)) ||
         (position.x > (SCREEN_WIDTH + margin )) ||
         (position.y < (0 - margin)) ||
         (position.y > (SCREEN_HEIGHT + margin)); 
}
