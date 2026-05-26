#ifndef GRAPHIC_OPERATIONS_H
#define GRAPHIC_OPERATIONS_H
#include "raymath.h"

void rotate_point(Vector2& point, const Vector2& origin, float angle) ;
void translate_point(Vector2& point, const Vector2& force) ;
Vector2 calculate_normal(const Vector2& side) ;

#endif
