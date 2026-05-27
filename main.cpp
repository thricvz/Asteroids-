#include "include/GameObjects/BulletManager.hpp"

#include "include/Config.hpp"
#include "raylib.h"
#include "raymath.h"

#include "include/GameObjects/Asteroids.hpp"
#include "include/GameObjects/AsteroidManager.hpp"
#include "include/GameObjects/Ship.hpp"
#include "include/graphics_operations.hpp"
#include "include/Timer.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <cmath>

Vector2 screen_center{SCREEN_WIDTH/2., SCREEN_HEIGHT/2.};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids by Thricvz");
    SetTargetFPS(FRAME_RATE);               
    
    AsteroidManager* const  asteroids = AsteroidManager::instance(0.7);
    BulletManager bullets(25.0f, BLUE );
    Ship thousand_sunny(screen_center, 18.0f, &bullets);

    srand(time(0));

    while (!WindowShouldClose())    
    {
        BeginDrawing();
          
        if (! thousand_sunny.is_destroyed()) {
          thousand_sunny.update(); 
          thousand_sunny.display_info();

          thousand_sunny.draw();
          bullets.draw();
          asteroids->draw();


          thousand_sunny.handle_collisions(asteroids);
          asteroids->handle_collsions(bullets);

          asteroids->spawn_timer.keep_up();

          bullets.clean_up();
          asteroids->clean_up();
          ClearBackground(BLACK);

        } else {
          const std::string game_end_message("You died dummy");
          const int32_t font_size {20};
          const int32_t x_offset = (game_end_message.size() / 2) * font_size;

          DrawText(
              game_end_message.c_str(),
              screen_center.x - x_offset ,
              screen_center.y - font_size,
              font_size,
              RED
          );
        }

        EndDrawing();
    }

    CloseWindow();        
    return 0;
}
