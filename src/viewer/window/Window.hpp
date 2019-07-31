#pragma once

#include <memory>
#include <atomic>
#include <vector>
#include <thread>
#include <functional>
#include "glfw/glfw3.h"
#include "../interfaces/IRendererContext.hpp"
#include "InputControl.hpp"

namespace view
{
  class Window;
  using window_t = Window*;
  //using window_t = std::shared_ptr<Window>;
  using window_handle_t = GLFWwindow*;

  class Window
  {
    window_handle_t _window;
    render::render_context_t _rendererContext;
    inputcontrol_t _inputControl;
    std::thread _worker;
    std::atomic<bool> _isRunning;

  public:
    static window_t GetInstance(window_handle_t window)
    {
      return static_cast<window_t>(glfwGetWindowUserPointer(window));
    }

    Window();
    ~Window();
    bool Init();
    bool CreateWindow(std::string title, size_t width = 1024, size_t height = 768);
    void AttachContext(render::render_context_t);
    void Show();
    void AsyncShow(render::render_context_t context, std::string title, size_t width = 1024, size_t height = 768);
    const window_handle_t native_handle() const { return _window; }
    inputcontrol_t GetInputControl() { return _inputControl; }
  };
}