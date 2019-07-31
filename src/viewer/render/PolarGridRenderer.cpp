#include "PolarGridRenderer.hpp"
#include "../shaders/GlslShaders.hpp"

namespace render
{
  PolarGridRenderer::PolarGridRenderer(render_context_t renderContext, float radialInterval, float radialExtent, float angularInterval, float angularExtent)
      : RendererBase(renderContext)
  {
    _program.LinkShaders(ogl::VertexShader(vec4VextexShader), ogl::FragmentShader(uniformFragmentShader));
    _mvpMatrix = matrix4x4_uniform(_program, "mvp_matrix", glm::mat4(1.0f));
    _lineColor = color_uniform(_program, "fragmentColor", color_gray);

    CreateVertices(radialInterval, radialExtent, angularInterval, angularExtent);
  }

  void PolarGridRenderer::Render()
  {
    _program.Activate();

    _mvpMatrix.Update(_camera->GetProjectionMatrix() * _camera->GetViewMatrix());
    _lineColor.Update();

    _vao.Activate();

    _vertices.Draw(GL_LINES);
  }

  void PolarGridRenderer::CreateVertices(float radialInterval, float radialExtent, float angularInterval, float angularExtent)
  {
    vertices_t vertices;

    float arcLength = 0.0f;
    float arcLengthMin = 0.5f;

    float rmax = radialExtent;
    float dr = radialInterval;

    float amax = angularExtent;
    float da = angularInterval;

    //lines from center to outer circle
    for(float a = 0.0f; a <= amax; a += da)
    {
      vertices.push_back({0, 0, 0, 1});
      vertices.push_back({rmax * sinf(a), rmax * cosf(a), 0, 1});
    }

    //circular lines
    for(float r = dr; r <= rmax; r += dr)
    {
      arcLength = r * amax;
      size_t k = std::max<size_t>(size_t(arcLength / arcLengthMin) + 1, 2);
      da = amax / (float(k) - 1.0f);

      for(size_t j = 0; j < k - 1; ++j)
      {
        float a = j * da;
        vertices.push_back({r * sinf(a), r * cosf(a), 0, 1});
        vertices.push_back({r * sinf(a + da), r * cosf(a + da), 0, 1});
      }
    }

    _vertices.Load(vertices.data()->data(), vertices.size() * 4);
    _pointAttr = ogl::VertexAttribute<vertex_t>(_program, "point");
  }
}