#pragma once

#include "../RendererBase.hpp"

namespace render
{
  class CubeRenderer : public RendererBase
  {
    ogl::VAO _vao;
    ogl::EBO _ebo;
    color_uniform _lineColor;
    ogl::VertexAttribute<vertex_t> _pointAttr;
    glm::mat4x4 _modelMatrix;

  public:
    CubeRenderer(render_context_t, glm::mat4x4 modelMatrix);
    virtual void Render();
    virtual glm::mat4x4 model_matrix();
  };
}