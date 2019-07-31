#pragma once

#include <memory>
#include "common/mathex.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../interfaces/ICamera.hpp"

namespace render
{
  class Camera : public ICamera
  {
  private:
    struct
    {
      float fov;
      float nearPlane = 0.1f;
      float farPlane = 10000.0f;
      float aspectRatio;

      auto GetProjectionMatrix()
      {
        return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
      }
    } _frustum;

    glm::mat4x4 _projectionMatrix;
    glm::mat4x4 _viewMatrix;
    glm::vec3 _position;
    glm::vec3 _resetPosition;
    glm::vec3 _direction;
    glm::vec3 _right;
    glm::vec3 _up;
    glm::vec3 _scale;
    glm::vec3 _worldUp;
    float _yaw;
    float _pitch;

    void UpdateViewMatrix()
    {
      // Direction : Spherical coordinates to Cartesian coordinates conversion
      _direction = glm::normalize(glm::vec3{cos(_pitch) * sin(_yaw), sin(_pitch), cos(_pitch) * cos(_yaw)});
      //_right		= glm::normalize(glm::vec3{ sin(_yaw - mathex::halfPI<float>), 0, cos(_yaw - mathex::halfPI<float>) });
      _right = glm::normalize(glm::cross(_direction, _worldUp));
      _up = glm::normalize(glm::cross(_right, _direction)); // Up vector : perpendicular to both direction and right

      _viewMatrix = glm::lookAt(_position, _position + _direction, _up);
      _viewMatrix = glm::scale(_viewMatrix, _scale);
    }

  public:
    Camera()
    {
      _worldUp = glm::vec3(0, 1, 0);
      _resetPosition = glm::vec3(0, 0, 0);

      Reset();
    }

    void Reset()
    {
      _frustum.fov = mathex::DegreeToRad(60.0f);
      _frustum.nearPlane = 0.1f;
      _frustum.farPlane = 10000.0f;
      _frustum.aspectRatio = 1.0f;
      _projectionMatrix = _frustum.GetProjectionMatrix();
      _scale = glm::vec3(1, 1, 1);
      _position = glm::vec3(0, 0, 0);
      _yaw = mathex::PI<float>; // Radians: Initial yaw/horizontal angle : toward -Z
      _pitch = 0.0f;            // pitch/vertical angle : 0, look at the horizon
      UpdateViewMatrix();

      if(_resetPosition.length() > 0)
        Move(_resetPosition);
    }

    void SetResetPosition(glm::vec3 pos)
    {
      _resetPosition = pos;
      Reset();
    }

    void Rotate(glm::vec2 delta)
    {
      _pitch += delta.x;
      _yaw += delta.y;
      UpdateViewMatrix();
    }

    void Move(glm::vec3 delta)
    {
      _position += _right * delta.x;
      _position += _up * delta.y;
      _position += _direction * delta.z;
      UpdateViewMatrix();
    }

    void Scale(glm::vec3 delta)
    {
      _scale += delta;
      _scale = glm::abs(_scale);
      UpdateViewMatrix();
    }

    const glm::mat4x4 GetViewMatrix() override
    {
      return _viewMatrix;
    }

    const glm::mat4x4 GetProjectionMatrix() override
    {
      return _projectionMatrix;
    }
  };
}