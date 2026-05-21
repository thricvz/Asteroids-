#ifndef SHIP_H
#define SHIP_H


#include "Triangle.hpp"
#include "../Timer.hpp"

class Ship : public Triangle {
  public: 
    Ship(const Vector2& start_position, float width, BulletManager* bullets_manager) : 
      Triangle(start_position, width / 2., BLUE) ,
      m_bullets_manager(bullets_manager),
      m_ammo_recharge_timer(0.1, FRAME_RATE) 
    {
      m_ammo_recharge_timer.on_expiry([this](){
        this->recharge_ammo();
      });

    };



  void update() {
    point_in_mouse_direction();
    move();
    shoot();
    m_ammo_recharge_timer.keep_up();
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

    bool is_out_of_bounds(const Vector2& position) const {
      return false;
    }

    BulletManager* const m_bullets_manager;
    Vector2 m_direction{ 0, -1};
    float m_speed{10.f};

    uint8_t m_ammo{1};
    Timer m_ammo_recharge_timer;     
};

#endif
