#pragma once

#include <string>
#include "Program.hpp"

namespace ogl
{
  template<typename T, typename type_trait>
  class Uniform : public OglObjectBase<Uniform<T, type_trait>, GLint>
  {
    using data_type = T;

    data_type _data;

    virtual bool isValid() const
    {
      return (this->_id >= 0);
    }

  public:
    static typename Uniform::id_type Allocator() { return -1; }
    static typename Uniform::id_type Allocator(Program const& program, std::string name) { return glGetUniformLocation(program.id(), name.c_str()); }
    static void Deallocator(typename Uniform::id_type id) {}
    static void Activator(typename Uniform::id_type id, data_type data) { type_trait::set(id, data); }

    Uniform()
    {
    }

    Uniform(Program const& program, std::string name, data_type def = data_type())
        : OglObjectBase<Uniform<T, type_trait>, GLint>(program, name),
          _data(def)
    {
    }

    void Update(const data_type v)
    {
      _data = v;
      Update();
    }

    void Update()
    {
      this->Activate(_data);
    }
  };
}