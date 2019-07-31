#include <iostream>
#include <functional>
#include "common/functional.hpp"
#include "common/mathex.hpp"
#include "RendererContext.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ogl/Utils.hpp"

namespace render
{
  RendererContext::RendererContext()
      : _width(0), _height(0)
  {
    Init();
  }

  RendererContext::~RendererContext()
  {
  }

  bool RendererContext::Init()
  {
    auto e = ogl::GetGlError();
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glEnable(GL_MULTISAMPLE); // glad
    glEnable(GL_CULL_FACE);

    _camera = std::make_shared<Camera>();
    return true;
  }

  void RendererContext::Render()
  {
    vao.Activate();

    glClearColor(0.0f, 0.2f, 0.2f, 0.9f); // Dark blue background
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1.0f);

    func::for_each(_renderers, std::mem_fn(&IRendererObject::Render));
  }

  void RendererContext::SetSize(size_t width, size_t height)
  {
    _width = width;
    _height = height;
    glViewport(0, 0, (GLsizei)_width, (GLsizei)_height);
  }

  renderer_t RendererContext::AddRenderer(renderer_t renderer)
  {
    _renderers.emplace_back(renderer);
    return renderer;
  }
}