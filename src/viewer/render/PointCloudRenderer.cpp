
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "PointCloudRenderer.hpp"

namespace render
{
  PointCloudRenderer::PointCloudRenderer()
  {
    //AddPoints({ { -10, -10, -10, 1.0f } , { 10, 10, 10, 1.0f } });
    //AddPoints({ { 0, 0, 0, 1.0f },{ 10, 10, 10, 1.0f } });
    AddVertices({{0, 0, 0, 1.0f}});
  }

  void PointCloudRenderer::Render()
  {
    // 2do: port this to >= opengl 3

    //glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
    //glPushMatrix();             // save current modelview matrix

    //glm::mat4x4 viewMatrix;
    //glMultMatrixf(glm::value_ptr(viewMatrix));

    //glPointSize(15);
    //glLineWidth(150);
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);

    //glVertexPointer(4, GL_FLOAT, 0, _vertices.data());
    //glColorPointer(4, GL_FLOAT, 0, _colors.data());
    //
    //glDrawArrays(GL_POINTS, 0, GLsizei(_vertices.size()));

    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);

    //// restore modelview matrix
    //glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
    //glPopMatrix();              // restore to previous modelview matrix
  }

  void PointCloudRenderer::AddVertices(vertices_t vertices)
  {
    _vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
    _colors.insert(_colors.end(), vertices.size(), {1.0f, 0.0f, 0.0f, 1.0f});
  }
}