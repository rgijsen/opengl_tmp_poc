#pragma once

namespace render
{
  class IRendererObject
  {
  public:
    virtual void Render() = 0;
  };
}