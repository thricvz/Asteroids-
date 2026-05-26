#include "include/GameObjects/BulletManager.hpp"
#define FRAME_RATE 30
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

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
          
        thousand_sunny.update(); 
       
          
        thousand_sunny.draw();
        bullets.draw();
        asteroids->draw();

        asteroids->handle_collsions(bullets);

        asteroids->spawn_timer.keep_up();

        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();        
    return 0;
}
