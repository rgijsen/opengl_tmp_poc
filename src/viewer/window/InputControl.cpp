#include <algorithm>
#include "InputControl.hpp"
#include "Window.hpp"

namespace view
{
  InputControl::InputControl(Window* window)
      : _events(5, [](auto e) { return e.key; }, [](auto lhs, auto rhs) { return lhs.key == rhs.key; })
  {
    auto windowHandle = window->native_handle();

    if(windowHandle)
    {
      // Ensure we can capture the escape key being pressed below
      glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, GL_TRUE);
      //glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      auto callback = [](auto native_window, auto... param) { Window::GetInstance(native_window)->GetInputControl()->Input(param...); };

      glfwSetKeyCallback(windowHandle, callback);
      glfwSetMouseButtonCallback(windowHandle, callback);
      glfwSetCursorPosCallback(windowHandle, callback);
    }

    _lastTimestamp = std::chrono::steady_clock::now();
  }

  void InputControl::Input(int key, int scancode, int action, int mods)
  {
    if(action == GLFW_PRESS)
    {
      _events.emplace(handler_event_t{key});
      Update();
    }
    else if(action == GLFW_RELEASE)
    {
      _events.erase(key);
    }
  }

  void InputControl::Input(int button, int action, int mods)
  {
    if(button == 0)
      button = MOUSE_LEFT_BUTTON_DOWN;
    else if(button == 1)
      button = MOUSE_RIGHT_BUTTON_DOWN;
    Input(button, 0, action, mods);
  }

  void InputControl::Input(double xPos, double yPos)
  {
    if(glm::length(_lastMousePosition) == 0)
      _lastMousePosition = {xPos, yPos};
    else
    {
      glm::vec2 currentMousePosition = {xPos, yPos};
      auto mouseOffset = currentMousePosition - _lastMousePosition;
      _lastMousePosition = currentMousePosition;
      _events.emplace(handler_event_t{MOUSE_MOVE, mouseOffset});
      Update();
    }
  }

  void InputControl::Update()
  {
    std::for_each(_handlers.begin(), _handlers.end(), [this](auto handler) { handler(*this); });
  }

  bool InputControl::IsShiftDown() const
  {
    return (IsControlDown(GLFW_KEY_LEFT_SHIFT) ||
            IsControlDown(GLFW_KEY_RIGHT_SHIFT));
  }

  bool InputControl::IsControlDown(int key) const
  {
    return (_events.find(key) != _events.end());
  }

  float InputControl::GetDeltaTime()
  {
    using SinglePrecisionSeconds = std::chrono::duration<float, std::chrono::seconds::period>;

    auto currentTime = std::chrono::steady_clock::now();
    auto deltaTime = SinglePrecisionSeconds(currentTime - _lastTimestamp);
    _lastTimestamp = currentTime;

    return deltaTime.count();
  }

  glm::vec2 InputControl::GetMouseOffset()
  {
    auto mouseMoveIt = _events.find(MOUSE_MOVE);
    if(mouseMoveIt != _events.end())
    {
      auto mouseOffset = mouseMoveIt->mouseOffset;
      _events.erase(MOUSE_MOVE);
      return mouseOffset;
    }
    return glm::vec2();
  }

  void InputControl::AddHandler(InputHandler_t handler)
  {
    _handlers.push_back(handler);
  }
}
