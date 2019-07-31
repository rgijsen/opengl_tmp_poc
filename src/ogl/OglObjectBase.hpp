#pragma once

#include <GL/glew.h>

namespace ogl
{
  template<typename T, typename id_t = GLuint>
  class OglObjectBase
  {
  protected:
    using id_type = id_t;
    using impl_type = T;
    using base_type = OglObjectBase<impl_type, id_type>;

    id_type _id;

    inline virtual bool isValid() const
    {
      return (_id != 0);
    }

  public:
    template<typename... Ts>
    OglObjectBase(Ts&&... args)
    {
      _id = impl_type::Allocator(args...);
    }

    virtual ~OglObjectBase()
    {
      if(isValid())
        impl_type::Deallocator(_id);
    }

    OglObjectBase(const OglObjectBase&) = delete;
    OglObjectBase& operator=(const OglObjectBase&) = delete;

    OglObjectBase(OglObjectBase&& other)
    {
      *this = std::move(other);
    }

    OglObjectBase& operator=(OglObjectBase&& other)
    {
      _id = other._id;
      other._id = 0;
      return *this;
    }

    template<typename... Ts>
    void Activate(Ts... args)
    {
      if(isValid())
        impl_type::Activator(_id, args...);
    }

    const id_type id() const
    {
      return _id;
    }
  };
}