#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "AxisRenderer.hpp"
#include "../shaders/GlslShaders.hpp"

namespace render
{
  AxisRenderer::AxisRenderer(render_context_t rendererContext)
      : RendererBase(rendererContext)
  {
    vertices_t vertices;
    colors_t colors;
    auto addAxis = [&vertices, &colors](vertex_t axis, color_t color) {
      vertices.push_back({0, 0, 0, 1});
      vertices.push_back(axis);
      colors.push_back(color);
      colors.push_back(color);
    };

    addAxis(vertex_t(1, 0, 0, 1), color_red);
    addAxis(vertex_t(0, 1, 0, 1), color_green);
    addAxis(vertex_t(0, 0, 1, 1), color_blue);

    _program.LinkShaders(ogl::VertexShader(simpleVertexShader), ogl::FragmentShader(simpleFragmentShader));
    _mvpMatrix = matrix4x4_uniform(_program, "mvp_matrix", glm::mat4(1.0f));

    _vertices.Load(vertices.data()->data(), vertices.size() * 4);
    _pointAttr = ogl::VertexAttribute<vertex_t>(_program, "point");
    _colors.Load(colors.data()->data(), colors.size() * 4);
    _colorAttr = ogl::VertexAttribute<color_t>(_program, "color");
  }

  void AxisRenderer::Render()
  {
    _program.Activate();
    _mvpMatrix.Update(_camera->GetViewMatrix());
    _vao.Activate();
    _vertices.Draw(GL_LINES);
  }
}