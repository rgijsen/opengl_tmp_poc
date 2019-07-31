#pragma once

#include "OglObjectBase.hpp"

namespace ogl
{
  // vertex array object
  class VAO : public OglObjectBase<VAO>
  {
  public:
    static typename VAO::id_type Allocator()
    {
      id_type id;
      glGenVertexArrays(1, &id);
      return id;
    }
    static void Deallocator(typename VAO::id_type id) { glDeleteVertexArrays(1, &id); }
    static void Activator(typename VAO::id_type id) { glBindVertexArray(id); }

    VAO()
        : base_type()
    {
      Activate();
    }
  };
}