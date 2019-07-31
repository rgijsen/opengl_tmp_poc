
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "PlotRenderer.hpp"
#include "../shaders/GlslShaders.hpp"

namespace render
{
  PlotRenderer::PlotRenderer(render_context_t rendererContext)
      : _lineWidth(2.0f)
  {
    _camera = rendererContext->GetCamera();
    //_program.LinkShaders(ogl::VertexShader(plotVertexShader), ogl::FragmentShader(plotFragmentShader));
    _program.LinkShaders(ogl::VertexShader(primitiveVertexShader),
                         ogl::GeometryShader(primitiveGeometryShader),
                         ogl::FragmentShader(primitiveFragmentShader));
    _viewMatrix = matrix4x4_uniform(_program, "viewMatrix", glm::mat4(1.0f));
    _lineColor = color_uniform(_program, "fragmentColor", color_red);
  }

  void PlotRenderer::Render()
  {
    glLineWidth(_lineWidth); // todo: remove ogl call

    _program.Activate();

    _viewMatrix.Update(_camera->GetViewMatrix());
    _lineColor.Update();

    _vao.Activate();

    _vertices.Draw(GL_POINTS);
  }

  void PlotRenderer::UpdatePoints(const points_t* points)
  {
    _vao.Activate();
    _vertices.Load(points->data()->data(), points->size() * 2);
    _pointAttr = ogl::VertexAttribute<point_t>(_program, "point");
  }
}