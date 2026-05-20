#include "raylib.h"
#include "raymath.h"

#include "include/graphics_operations.hpp"
#include "include/GameObjects/Asteroids.hpp"
#include "include/Timer.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <cmath>

#define FRAME_RATE 30
#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT  800

Timer ASTEROID_SPAWN_TIMER(0.7, FRAME_RATE);

std::vector<Asteroid> asteroids;

Vector2 random_asteroid_spawn_position(uint32_t spawn_radius) {
  float angle = rand() % 360;
  Vector2 spawn_position{
    spawn_radius * cos(angle),
    spawn_radius * sin(angle)
  };

  return Vector2Add(spawn_position , Vector2{SCREEN_WIDTH/2., SCREEN_HEIGHT/2.});
};

Asteroid::Size random_asteroid_size() {
  uint8_t size_choice = rand() % 3;
  switch (size_choice) {
    case 0:  return Asteroid::Size::SMALL;
    case 1:  return Asteroid::Size::MEDIUM;
    case 2:  return Asteroid::Size::BIG;
  }
};

float random_asteroid_speed() {
  return std::max(static_cast<float>(rand() % 5), 0.7f); 
}


Vector2 random_center_deviation() {
  const Vector2 center{SCREEN_WIDTH/2. , SCREEN_HEIGHT/2.};
  
  const uint8_t deviation_factor = 3; 
  const float deviation_x =  rand() % (SCREEN_WIDTH / deviation_factor);
  const float deviation_y =  rand() % (SCREEN_HEIGHT /  deviation_factor); 
  const Vector2& deviated_center =  Vector2Add(center, Vector2{deviation_x, deviation_y});
    
  return deviated_center ;
}


Vector2 direction_from_to(const Vector2& spawn, const Vector2& point) {
  const Vector2& distance_from_center = Vector2Subtract(point, spawn);
  return Vector2Normalize(distance_from_center);
}

void spawn_asteroid() {
  const auto spawn_circle_radius {
    std::max(
      SCREEN_HEIGHT / 2,
      SCREEN_WIDTH / 2
    )
  };

  const Vector2& spawn_position = random_asteroid_spawn_position(spawn_circle_radius);
  const Vector2& asteroid_direction = direction_from_to(spawn_position, random_center_deviation());

  asteroids.emplace_back(
      spawn_position,
      asteroid_direction,
      random_asteroid_speed(),
      random_asteroid_size(),
      (rand() % 10 + 1) * 0.01
  );
}




int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids by Thricvz");
    SetTargetFPS(FRAME_RATE);               
    
    ASTEROID_SPAWN_TIMER.on_expiry(spawn_asteroid);

    srand(time(0));


    while (!WindowShouldClose())    
    {
        BeginDrawing();
          
        
        for (auto& asteroid: asteroids) {
          asteroid.move();
          asteroid.draw();
        }

        ClearBackground(BLACK);
  

        ASTEROID_SPAWN_TIMER.keep_up();

        EndDrawing();
    }
    CloseWindow();        
    return 0;
}
