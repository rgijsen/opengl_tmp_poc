#pragma once

#include "RendererBase.hpp"

namespace render
{
  class PolarGridRenderer : public RendererBase
  {
    ogl::VAO _vao;
    color_uniform _lineColor;
    ogl::VertexAttribute<vertex_t> _pointAttr;

    void CreateVertices(float radialInterval, float radialExtent, float angularInterval, float angularExtent);

  public:
    PolarGridRenderer(render_context_t, float radialInterval, float radialExtent, float angularInterval, float angularExtent);
    virtual void Render();
  };
}