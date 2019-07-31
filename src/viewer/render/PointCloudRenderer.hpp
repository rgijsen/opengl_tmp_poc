#pragma once

#include "RendererTypes.hpp"
#include "../interfaces/IRendererObject.hpp"

namespace render
{
  class PointCloudRenderer : public IRendererObject
  {
    vertices_t _vertices;
    colors_t _colors;

  public:
    PointCloudRenderer();
    virtual void Render();
    void AddVertices(vertices_t);
  };
}