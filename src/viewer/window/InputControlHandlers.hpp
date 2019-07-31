#pragma once

#include "InputControl.hpp"
#include "../render/Camera.hpp"
#include "glfw/glfw3.h"

namespace view
{
  struct InputControlHandlers
  {
    static float CalculateAcceleration(InputControl& inputControl)
    {
      return inputControl.IsShiftDown() ? 5.0f : 1.0f;
    }

    static float CalculateTimeDelta(InputControl& inputControl)
    {
      auto deltaTime = inputControl.GetDeltaTime();
      deltaTime = (float)1 / 60;
      return deltaTime * CalculateAcceleration(inputControl);
    }

    static void InputHandler2D(render::camera_t camera, InputControl& inputControl)
    {
      auto delta = CalculateTimeDelta(inputControl);

      if(inputControl.IsControlDown(GLFW_KEY_R))
        camera->Reset();
      else if(inputControl.IsControlDown(GLFW_KEY_UP))
        camera->Move(glm::vec3(0, delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_DOWN))
        camera->Move(glm::vec3(0, -delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_RIGHT))
        camera->Move(glm::vec3(delta, 0, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_LEFT))
        camera->Move(glm::vec3(-delta, 0, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_PAGE_UP))
        camera->Scale(glm::vec3(-delta / 10, -delta / 10, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_PAGE_DOWN))
        camera->Scale(glm::vec3(delta / 10, delta / 10, 0));
    };

    static void MouseHandler2D(render::camera_t camera, InputControl& inputControl)
    {
			auto offset = inputControl.GetMouseOffset();
			offset /= 500;
			if(glm::length(offset) > 0)
			{
				if(inputControl.IsControlDown(MOUSE_LEFT_BUTTON_DOWN))
					camera->Move(glm::vec3(-offset.x, offset.y, 0));
				else if(inputControl.IsControlDown(MOUSE_RIGHT_BUTTON_DOWN))
					camera->Scale(glm::vec3(offset.x, offset.y, 0));
			}
    }

    static void InputHandler3D(render::camera_t camera, InputControl& inputControl)
    {
      auto delta = CalculateTimeDelta(inputControl);

      if(inputControl.IsControlDown(GLFW_KEY_R))
        camera->Reset();
      else if(inputControl.IsControlDown(GLFW_KEY_UP))
        camera->Move(glm::vec3(0, delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_DOWN))
        camera->Move(glm::vec3(0, -delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_RIGHT))
        camera->Move(glm::vec3(delta, 0, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_LEFT))
        camera->Move(glm::vec3(-delta, 0, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_HOME))
        camera->Move(glm::vec3(0, 0, delta));
      else if(inputControl.IsControlDown(GLFW_KEY_END))
        camera->Move(glm::vec3(0, 0, -delta));
      else if(inputControl.IsControlDown(GLFW_KEY_PAGE_UP))
        camera->Rotate(glm::vec2(delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_PAGE_DOWN))
        camera->Rotate(glm::vec2(-delta, 0));
      else if(inputControl.IsControlDown(GLFW_KEY_INSERT))
        camera->Rotate(glm::vec2(0, delta));
      else if(inputControl.IsControlDown(GLFW_KEY_DELETE))
        camera->Rotate(glm::vec2(0, -delta));
      else if(inputControl.IsControlDown(GLFW_KEY_R))
        camera->Reset();
    }

    static void MouseHandler3D(render::camera_t camera, InputControl& inputControl)
    {
      if(inputControl.IsControlDown(MOUSE_LEFT_BUTTON_DOWN))
      {
        auto offset = inputControl.GetMouseOffset();
        offset /= 500;
        if(glm::length(offset) > 0)
          camera->Rotate(offset);
      }
    }
  };
}
