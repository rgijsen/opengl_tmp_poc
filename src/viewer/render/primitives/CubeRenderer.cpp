#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "CubeRenderer.hpp"
#include "../../shaders/GlslShaders.hpp"

namespace render
{
  CubeRenderer::CubeRenderer(render_context_t rendererContext, glm::mat4x4 modelMatrix)
      : RendererBase(rendererContext), _modelMatrix{modelMatrix}
  {
    _program.LinkShaders(ogl::VertexShader(vec4VextexShader), ogl::FragmentShader(uniformFragmentShader));
    _mvpMatrix = matrix4x4_uniform(_program, "mvp_matrix", glm::mat4(1.0f));
    _lineColor = color_uniform(_program, "fragmentColor", color_yellow);

    float u = 0.5f;
    vertices_t vertices;
    vertices.push_back({-u, -u, u, 1});
    vertices.push_back({u, -u, u, 1});
    vertices.push_back({u, u, u, 1});
    vertices.push_back({-u, u, u, 1});
    vertices.push_back({-u, -u, -u, 1});
    vertices.push_back({u, -u, -u, 1});
    vertices.push_back({u, u, -u, 1});
    vertices.push_back({-u, u, -u, 1});

    _vertices.Load(vertices.data()->data(), vertices.size() * 4);
    _ebo.Load({0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7});
    _pointAttr = ogl::VertexAttribute<vertex_t>(_program, "point");
  }

  glm::mat4x4 CubeRenderer::model_matrix()
  {
    return _modelMatrix;
  }

  void CubeRenderer::Render()
  {
    _program.Activate();

    _mvpMatrix.Update(mvp_matrix());
    _lineColor.Update();

    _vao.Activate();

    //glDrawArrays(GL_LINES, 0, GLsizei(_vertices.size()));
    //glDrawElements(GL_LINES, (GLsizei)_ebo.size(), GL_UNSIGNED_INT, 0);
    _ebo.Draw(GL_LINES);
  }
}