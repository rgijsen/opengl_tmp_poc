#pragma once

#include <fstream>
#include <sstream>
#include "OglObjectBase.hpp"

namespace ogl
{
  class Shader : public OglObjectBase<Shader>
  {
  public:
    static id_type Allocator(GLenum type) { return glCreateShader(type); }
    static void Deallocator(id_type id) { glDeleteShader(id); }

    Shader(GLenum type, std::string shaderSource)
        : base_type(type)
    {
      Create(shaderSource);
    }

    bool CreateFromFile(std::string path)
    {
      // Read the shader code from the file
      std::string s;
      std::ifstream ifs(path.c_str(), std::ios::in);
      if(ifs.is_open())
      {
        std::stringstream stream;
        stream << ifs.rdbuf();
        s = stream.str();
        ifs.close();
      }
      else
      {
        logging("Unable to open " + path);
        getchar();
        return false;
      }

      logging("Compiling shader : " + path);
      return Create(s);
    }

    bool Create(std::string shaderCode)
    {
      // Compile Shader
      char const* sourcePointer = shaderCode.c_str();
      glShaderSource(_id, 1, &sourcePointer, NULL);
      glCompileShader(_id);

      return CheckShaderError(_id);
    }
  };

  template<GLenum type>
  struct ShaderImpl : Shader
  {
    ShaderImpl(std::string shaderCode)
        : Shader(type, shaderCode)
    {
    }
  };

  using VertexShader = ShaderImpl<GL_VERTEX_SHADER>;
  using TesselationControlShader = ShaderImpl<GL_TESS_CONTROL_SHADER>;
  using TesselationEvalShader = ShaderImpl<GL_TESS_EVALUATION_SHADER>;
  using GeometryShader = ShaderImpl<GL_GEOMETRY_SHADER>;
  using FragmentShader = ShaderImpl<GL_FRAGMENT_SHADER>;
}