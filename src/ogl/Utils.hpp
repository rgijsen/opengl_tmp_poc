#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <GL/glew.h>

namespace ogl
{
#define logging(msg) std::cout << msg << std::endl;

  inline int GetGlError()
  {
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR)
    {
      //std::cout << "OpenGL error: " << err << std::endl;
      return err;
    }

    return GL_NO_ERROR;
  }

  typedef void (*get_param_t)(GLuint, GLenum, GLint*);
  typedef void (*get_loginfo_t)(GLuint, GLsizei, GLsizei*, GLchar*);

  inline bool CheckAndLogError(GLuint id, std::string msg_prefix, get_param_t get_param, get_loginfo_t get_loginfo)
  {
    //GLint result = GL_FALSE;
    //get_param(id, GL_LINK_STATUS, &result);

    int infoLogLength;
    get_param(id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0)
    {
      std::vector<char> errorMessage(infoLogLength + 1);
      get_loginfo(id, infoLogLength, NULL, &errorMessage[0]);
      logging(msg_prefix + &errorMessage[0]);
      return false;
    }

    return true;
  }

  constexpr auto CheckProgramError = [](GLuint id) { return CheckAndLogError(id, "Program error: ", glGetProgramiv, glGetProgramInfoLog); };
  constexpr auto CheckShaderError = [](GLuint id) { return CheckAndLogError(id, "Shader error: ", glGetShaderiv, glGetShaderInfoLog); };
}