#pragma once

#include "RendererBase.hpp"

namespace render
{
  //using ver = Eigen::Matrix<GLfloat, 5, 5>;

  class AxisRenderer : public RendererBase
  {
    ogl::VAO _vao;
    ogl::VertexAttribute<vertex_t> _pointAttr;
    ogl::VertexAttribute<color_t> _colorAttr;

  public:
    AxisRenderer(render_context_t);
    virtual void Render();
  };
}