#pragma once

#include "OglObjectBase.hpp"

namespace ogl
{
  template<typename T, GLint type_t = GL_FLOAT>
  class VertexAttribute : public OglObjectBase<VertexAttribute<T, type_t>, GLint>
  {
    GLsizei _stride = 0;
    void* _offset = nullptr;

  protected:
    inline virtual bool isValid() const
    {
      return (this->_id >= 0);
    }

  public:
    static typename VertexAttribute::id_type Allocator(typename VertexAttribute::id_type id = -1) { return id; }
    static typename VertexAttribute::id_type Allocator(Program const& program, std::string name) { return glGetAttribLocation(program.id(), name.c_str()); }
    static void Deallocator(typename VertexAttribute::id_type id) { glDisableVertexAttribArray(id); }
    static void Activator(typename VertexAttribute::id_type id, GLsizei stride, const void* offset)
    {
      glEnableVertexAttribArray(id);
      glVertexAttribPointer(
          id,
          sizeof(T) / sizeof(type_t), // size
          type_t,                     // type
          GL_FALSE,                   // normalized
          stride,                     // stride
          (void*)offset               // array buffer offset
      );
    }

    VertexAttribute(Program const& program, std::string name, GLsizei stride = 0, const void* offset = nullptr)
        : OglObjectBase<VertexAttribute<T, type_t>, GLint>(program, name)
    {
      _stride = stride;
      _offset = offset;
      Activate();
    }

    VertexAttribute(Program const& program, std::string name, GLsizei stride, GLsizei offset)
        : VertexAttribute(program, name, stride, &offset)
    {
    }

    template<typename... Ts>
    VertexAttribute(Ts&... args)
        : OglObjectBase<VertexAttribute<T, type_t>, GLint>(args...)
    {
      Activate();
    }

    void Activate()
    {
      if(isValid())
        Activator(this->_id, _stride, _offset);
    }

    void Deactivate()
    {
      if(isValid())
        Deallocator(this->_id);
    }
  };

  template<typename T>
  struct attribute_guard
  {
    T& _attribute;

    attribute_guard(T& attribute)
        : _attribute(attribute)
    {
      _attribute.Activate();
    }

    ~attribute_guard()
    {
      _attribute.Deactivate();
    }
  };

  template<typename T>
  attribute_guard<T> make_attribute_guard(T& a)
  {
    return attribute_guard<T>(a);
  };
}