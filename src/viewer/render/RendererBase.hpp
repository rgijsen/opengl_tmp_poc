#pragma once

#include "RendererTypes.hpp"
#include "../interfaces/IRendererObject.hpp"
#include "../interfaces/IRendererContext.hpp"
#include "ogl/ogl.hpp"
#include "Camera.hpp"

namespace render
{
  class RendererBase : public IRendererObject
  {
  protected:
    camera_t _camera;
    ogl::Program _program;
    matrix4x4_uniform _mvpMatrix;
    ogl::VBO<GLfloat> _vertices;
    ogl::VBO<GLfloat> _colors;

    virtual glm::mat4x4 model_matrix()
    {
      return glm::mat4x4();
    }

    glm::mat4x4 mvp_matrix()
    {
      return _camera->GetProjectionMatrix() * _camera->GetViewMatrix() * model_matrix();
    };

  public:
    RendererBase(render_context_t rendererContext)
    {
      _camera = rendererContext->GetCamera();
    }
  };
}