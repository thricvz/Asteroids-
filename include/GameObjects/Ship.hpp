#ifndef SHIP_H
#define SHIP_H


#include "AsteroidManager.hpp"
#include "Triangle.hpp"
#include "../Timer.hpp"
#include <algorithm>

using namespace std::literals;

class Ship : public Triangle {
  public: 
    static inline Color SHIP_COLOR{BLUE};
    static inline Color IMMUNE_COLOR{GREEN};

    Ship(const Vector2& start_position, float width, BulletManager* bullets_manager) : 
      Triangle(start_position, width / 2., SHIP_COLOR) ,
      m_bullets_manager(bullets_manager),
      m_ammo_recharge_timer(0.1, FRAME_RATE),
      m_immunity_timer(2, FRAME_RATE) 
    {
      m_ammo_recharge_timer.on_expiry([this](){
        this->recharge_ammo();
      });
      
      m_immunity_timer.on_expiry([this]() {
        this->disable_immunity();
      });
    };

  void display_info() {
    std::string lives_left_str = "Lives : "s + std::to_string(m_lives);
    DrawText( lives_left_str.c_str(), 5, 5, 20, RAYWHITE ) ;

    if(m_immune) {
        DrawText( "Immune", 5, 30, 20, IMMUNE_COLOR ) ;
    }
  }

  void update() {
    point_in_mouse_direction();
    move();
    shoot();
    m_ammo_recharge_timer.keep_up();
  }

  void handle_collisions(const AsteroidManager* asteroid_manager) {
    if (m_immune) {
      m_immunity_timer.keep_up();
      return;
    }
    const auto& asteroid_begin = asteroid_manager->m_asteroids.begin();
    const auto& asteroid_end = asteroid_manager->m_asteroids.end();

    auto collided_with_ship = [this](const Asteroid& asteroid) {
        return CollisionManager::are_colliding(*this, asteroid) ;
    };

    if (std::any_of(asteroid_begin, asteroid_end, collided_with_ship)) {
      m_lives--;
      enable_immunity();
      m_immunity_timer.reset();

    }

  }

  bool is_destroyed() const {
    return m_lives == 0;
  }
  
  void disable_immunity() {
    m_immune = false;
    m_color = SHIP_COLOR;
  } 

  void enable_immunity() {
    m_immune = true;
    m_color = IMMUNE_COLOR;
  } 

  private:
    void point_in_mouse_direction() {
      const Vector2& mouse_position = GetMousePosition();
      const Vector2 previous_direction = m_direction;

      m_direction = Vector2Normalize(Vector2Subtract(mouse_position, m_center));
      rotate(Vector2Angle(previous_direction, m_direction));
    };

    void move() {
      // yes i know azerty keys ! : VIVE LA FRANCE , VIVE LA RÉPUBLIQUE!
      const char input_key = GetCharPressed();
      if( input_key == 'q') 
         move_left();

      if( input_key == 'd') 
         move_right();

      if( input_key == 'z') 
         move_forward();

      if( input_key == 's') 
         move_backwards();
    }


    void shoot() {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_ammo > 0 ) {
        const Vector2& bullet_spawn_position = Vector2Add(
          m_center,
          Vector2Scale(
            m_direction, 
            m_side
          ));

        const float bullet_radius {m_side/4};
        m_bullets_manager->spawn_bullet(bullet_spawn_position, m_direction, bullet_radius);

        m_ammo --;
        m_ammo_recharge_timer.reset();
      }
    }
   

    void recharge_ammo() {
      m_ammo = 1;
    }

    void move_right() {
      const Vector2& movement_direction = Vector2Scale(
          Vector2Rotate(m_direction, 90.f),
          m_speed
      );
      const Vector2& calculated_position = Vector2Add(m_center, movement_direction);

      if(!is_out_of_bounds(calculated_position)) 
        translate(movement_direction);
    }

    void move_left() {
      const Vector2& movement_direction = Vector2Scale(
          Vector2Rotate(m_direction, -90.f),
          m_speed
      );
      const Vector2& calculated_position = Vector2Add(m_center, movement_direction);

      if(!is_out_of_bounds(calculated_position)) 
        translate(movement_direction);
    }

    void move_forward() {
      const Vector2& movement_direction = Vector2Scale(
          m_direction,
          m_speed
      );
      const Vector2& calculated_position = Vector2Add(m_center, movement_direction);

      if(!is_out_of_bounds(calculated_position)) 
        translate(movement_direction);
    }

    void move_backwards() {
      const Vector2& movement_direction = Vector2Scale(
          Vector2Rotate(m_direction, -180.f),
          m_speed
      );
      const Vector2& calculated_position = Vector2Add(m_center, movement_direction);

      if(!is_out_of_bounds(calculated_position)) 
        translate(movement_direction);
    }


    Vector2 m_direction{ 0, -1};
    BulletManager* const m_bullets_manager;
    Timer m_ammo_recharge_timer;     
    Timer m_immunity_timer;     
      
    float m_speed{10.f};
    
    bool m_immune{false};
    uint8_t m_ammo{1};
    int8_t m_lives{3};
};

#endif
