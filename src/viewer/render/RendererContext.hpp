#pragma once

#include <vector>
#include "../interfaces/IRendererContext.hpp"
#include "../interfaces/IRendererObject.hpp"
#include "glm/glm.hpp"
#include "ogl/ogl.hpp"
#include "Camera.hpp"

namespace render
{
  class RendererContext : public render::IRendererContext
  {
    size_t _width;
    size_t _height;

    ogl::VAO vao;

    camera_t _camera;
    std::vector<renderer_t> _renderers;

  public:
    RendererContext();
    ~RendererContext();
    bool Init();
    virtual void Render();
    virtual void SetSize(size_t width, size_t height);
    virtual renderer_t AddRenderer(renderer_t);
    virtual camera_t GetCamera() { return _camera; };
  };
}