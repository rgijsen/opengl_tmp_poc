#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_set>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include "glfw/glfw3.h"

#define MOUSE_MOVE GLFW_KEY_LAST + 1
#define MOUSE_LEFT_BUTTON_DOWN GLFW_KEY_LAST + 2
#define MOUSE_RIGHT_BUTTON_DOWN GLFW_KEY_LAST + 3

namespace view
{
  class Window;

  class InputControl
  {
    struct handler_event_t
    {
      size_t key;
      glm::vec2 mouseOffset;

      handler_event_t(int k)
          : handler_event_t((size_t)k, {0.0f, 0.0f})
      {
      }

      handler_event_t(size_t k, glm::vec2 o)
          : key(k), mouseOffset(o)
      {
      }
    };

    using handler_event_hasher_t = std::function<size_t(handler_event_t const&)>;
    using handler_event_compare_t = std::function<bool(handler_event_t const&, handler_event_t const&)>;

    using InputHandler_t = std::function<void(InputControl&)>;

    std::unordered_set<handler_event_t, handler_event_hasher_t, handler_event_compare_t> _events;
    std::chrono::steady_clock::time_point _lastTimestamp;
    std::vector<InputHandler_t> _handlers;
    glm::vec2 _lastMousePosition;

  public:
    InputControl(Window*);
    // glfw window callback functions
    void Input(int key, int scancode, int action, int mods);
    void Input(int button, int action, int mods);
    void Input(double xPos, double yPos);

    void Update();
    bool IsShiftDown() const;
    bool IsControlDown(int key) const;
    glm::vec2 GetMouseOffset();
    float GetDeltaTime();
    void AddHandler(InputHandler_t);
  };

  using inputcontrol_t = std::shared_ptr<InputControl>;
}
