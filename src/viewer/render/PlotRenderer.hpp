#pragma once

#include "RendererTypes.hpp"
#include "../interfaces/IRendererObject.hpp"
#include "../interfaces/IRendererContext.hpp"
#include "ogl/ogl.hpp"
#include "RendererTypes.hpp"
#include "Camera.hpp"

namespace render
{
  class PlotRenderer : public IRendererObject
  {
    ogl::VAO _vao;
    float _lineWidth;
    ogl::Program _program;
    ogl::VBO<GLfloat> _vertices;
    matrix4x4_uniform _viewMatrix;
    color_uniform _lineColor;
    camera_t _camera;
    ogl::VertexAttribute<point_t> _pointAttr;

  public:
    PlotRenderer(render_context_t);
    void Render() override;
    void UpdatePoints(const points_t*);
  };
}