#pragma once

#include <memory>
#include "IRendererObject.hpp"
#include "ICamera.hpp"

namespace render
{
  using renderer_t = std::shared_ptr<IRendererObject>;

  template<typename T, typename... Args>
  std::shared_ptr<T> make_renderer(Args... args)
  {
    return std::make_shared<T>(args...);
  }

  class IRendererContext
  {
  public:
    virtual void Render() = 0;
    virtual void SetSize(size_t width, size_t height) = 0;
    virtual renderer_t AddRenderer(renderer_t) = 0;
    virtual camera_t GetCamera() = 0;
  };

  using render_context_t = std::shared_ptr<IRendererContext>;
}