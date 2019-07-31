#pragma once

#include <vector>
#include "Eigen/Dense"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ogl/Uniform.hpp"

namespace render
{
  using vertex_t = Eigen::Vector4f;
  using vertices_t = std::vector<vertex_t>;

  using point_t = Eigen::Vector2f;
  using points_t = std::vector<point_t>;

  using color_t = Eigen::Vector4f;
  using colors_t = std::vector<color_t>;

  const color_t color_red = color_t{1, 0, 0, 1};
  const color_t color_green = color_t{0, 1, 0, 1};
  const color_t color_blue = color_t{0, 0, 1, 1};
  const color_t color_black = color_t{0, 0, 0, 1};
  const color_t color_white = color_t{1, 1, 1, 1};
  const color_t color_yellow = color_t{1, 1, 0, 1};
  const color_t color_magenta = color_t{1, 0, 1, 1};
  const color_t color_gray = color_t{0.3f, 0.3f, 0.3f, 0.5f};

  struct color_uniform_trait
  {
    static void set(GLuint location, color_t color)
    {
      glUniform4fv(location, (GLsizei)1, color.data());
    }
  };

  struct matrix4x4_uniform_trait
  {
    static void set(GLuint location, glm::mat4x4 const& m)
    {
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
    }
  };

  using color_uniform = ogl::Uniform<color_t, color_uniform_trait>;
  using matrix4x4_uniform = ogl::Uniform<glm::mat4x4, matrix4x4_uniform_trait>;
}
