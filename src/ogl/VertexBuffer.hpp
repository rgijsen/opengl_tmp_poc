#pragma once

#include <vector>
#include "OglObjectBase.hpp"

namespace ogl
{
  template<size_t buffer_type, typename T>
  class BufferObject : public OglObjectBase<BufferObject<buffer_type, T>>
  {
    using data_type = T;

    size_t _size;

  public:
    static typename BufferObject::id_type Allocator()
    {
      typename BufferObject::id_type id;
      glGenBuffers(1, &id);
      return id;
    }
    static void Deallocator(typename BufferObject::id_type id) { glDeleteBuffers(1, &id); }
    static void Activator(typename BufferObject::id_type id) { glBindBuffer(buffer_type, id); }

    BufferObject()
        : OglObjectBase<BufferObject<buffer_type, T>>(), _size(0)
    {
    }

    BufferObject(std::vector<data_type> vertexData)
        : BufferObject()
    {
      Load(vertexData);
    }

    const size_t size() const
    {
      return _size;
    }

    void Load(const std::vector<data_type> vertexData)
    {
      Load(vertexData.data(), vertexData.size());
    }

    void Load(data_type const* vertexData, size_t size)
    {
      this->Activate();
      _size = size;
      glBufferData(buffer_type, sizeof(data_type) * size, vertexData, GL_STATIC_DRAW);
    }

    void Draw(int mode)
    {
      if constexpr(buffer_type == GL_ELEMENT_ARRAY_BUFFER)
        glDrawElements(mode, (GLsizei)size(), GL_UNSIGNED_INT, 0);
      else //if constexpr (buffer_type == GL_ARRAY_BUFFER)
        glDrawArrays(mode, 0, (GLsizei)size());
    }
  };

  template<typename T>
  using VBO = BufferObject<GL_ARRAY_BUFFER, T>;              // vertex buffer object
  using EBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GLuint>; // element buffer object
}