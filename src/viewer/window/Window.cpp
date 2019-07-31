
#include <GL/glew.h>
#include "common/logging.hpp"
#include "Window.hpp"

namespace view
{
  Window::Window()
      : _isRunning(false)
  {
    Init();
  }

  Window::~Window()
  {
    if(_worker.joinable())
    {
      _isRunning = false;
      _worker.join();
    }
  }

  bool Window::Init()
  {
    if(!glfwInit())
    {
      Log->LogInfo("Failed to initialize GLFW");
      return false;
    }

    return true;
  }

  bool Window::CreateWindow(std::string title, size_t width, size_t height)
  {
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA anti-alias
    //glfwWindowHint(GLFW_DEPTH_BITS, 24); // 24-bit depth buffer
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    int major = 4;
    int minor = 2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    ////glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Open a window and create its OpenGL context
    _window = glfwCreateWindow((int)width, (int)height, title.c_str(), NULL, NULL);
    if(_window == NULL)
    {
      Log->LogInfo("Failed to open GLFW window. If you have an Intel GPU, they are not compatible with OpenGL version: " + std::to_string(major) + "." + std::to_string(minor));
      glfwTerminate();
      return false;
    }

    glfwSetWindowUserPointer(_window, this);

    auto primary = glfwGetPrimaryMonitor();
    auto mode = glfwGetVideoMode(primary);

    glfwSetWindowPos(_window, (mode->width - (int)width) / 2, (mode->height - (int)height) / 2);
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    // Ensure we can capture the escape key being pressed below
    _inputControl = std::make_shared<InputControl>(this);

    glfwSetWindowSizeCallback(_window, [](window_handle_t window, int w, int h) {
      auto win = Window::GetInstance(window);
      if(win->_rendererContext)
        win->_rendererContext->SetSize(w, h);
    });

    glewExperimental = true; // Needed for core profile
    if(glewInit() != GLEW_OK)
    {
      Log->LogInfo("Failed to initialize GLEW");
      glfwTerminate();
      return false;
    }

    return true;
  }

  void Window::Show()
  {
    do
    {
      _inputControl->Update();

      if(_rendererContext)
        _rendererContext->Render();

      glfwSwapBuffers(_window);
      glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while(glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(_window) == 0);

    glfwDestroyWindow(_window);
  }

  void Window::AsyncShow(render::render_context_t context, std::string title, size_t width, size_t height)
  {
    _isRunning = true;
    _worker = std::thread([this, title, width, height, context]() {
      CreateWindow(title, width, height);
      AttachContext(context);
      Show();
    });
  }

  void Window::AttachContext(render::render_context_t context)
  {
    _rendererContext = context;

    if(_rendererContext)
    {
      int width, height;
      glfwGetWindowSize(_window, &width, &height);
      _rendererContext->SetSize(width, height);
    }
  }
}