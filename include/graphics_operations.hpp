#ifndef GRAPHIC_OPERATIONS_H
#define GRAPHIC_OPERATIONS_H
#include "raymath.h"
#include "Config.hpp"

void rotate_point(Vector2& point, const Vector2& origin, float angle) ;
void translate_point(Vector2& point, const Vector2& force) ;

Vector2 calculate_normal(const Vector2& side) ;

bool is_out_of_bounds(const Vector2& position, int32_t margin = 0) ;
#endif
