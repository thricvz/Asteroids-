#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <functional>

class Timer {
  public:
      Timer(float interval_seconds , uint32_t fps_count):
      m_interval ( static_cast<uint32_t>(interval_seconds * fps_count) ) {};
    
    void on_expiry(std::function<void()> callback ) {
      m_callback = callback;
    }

    void keep_up() noexcept (false) {
      if (!m_callback) 
        throw  std::runtime_error("Timer callback must be provided a function ");

      if (m_current_frame >= m_interval) {
        m_current_frame = 0;
        m_callback();
      }
      m_current_frame ++;
    };

    void reset() {
      m_current_frame = 0;
    }

  private:

    uint32_t m_current_frame {};
    uint32_t m_interval {};

    std::function<void()> m_callback = nullptr;
};


#endif
