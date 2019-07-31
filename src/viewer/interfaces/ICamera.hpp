#pragma once

#include <memory>
#include <glm/gtc/matrix_transform.hpp>

namespace render
{
  class ICamera
  {
  public:
    virtual const glm::mat4x4 GetViewMatrix() = 0;
    virtual const glm::mat4x4 GetProjectionMatrix() = 0;
    virtual void Move(glm::vec3 delta) = 0;
    virtual void Rotate(glm::vec2 delta) = 0;
    virtual void Scale(glm::vec3 delta) = 0;
    virtual void Reset() = 0;
    virtual void SetResetPosition(glm::vec3 pos) = 0;
  };

  using camera_t = std::shared_ptr<ICamera>;
}