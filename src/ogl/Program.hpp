#pragma once

#include <vector>
#include <algorithm>

#include "OglObjectBase.hpp"
#include "Utils.hpp"
#include "Shader.hpp"

namespace ogl
{
  class Program : public OglObjectBase<Program>
  {
  public:
    static id_type Allocator() { return glCreateProgram(); }
    static void Deallocator(id_type id) { glDeleteProgram(id); }
    static void Activator(id_type id) { glUseProgram(id); }

    template<typename... Ts>
    void LinkShaders(Ts&&... shadersList)
    {
      ogl::Shader shaders[] = {std::move(shadersList)...};

      auto for_each_shader = [id = _id, &shaders](auto fn) {
        std::for_each(std::begin(shaders), std::end(shaders), [id, fn](const auto& shader) { fn(id, shader.id()); });
      };

      for_each_shader(glAttachShader);
      glLinkProgram(_id);

      CheckProgramError(_id);

      for_each_shader(glDetachShader);
      //auto e = ogl::GetGlError();
    }
  };
}