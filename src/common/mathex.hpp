#pragma once

#include <algorithm>
//#include <math.h>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES // for C++
#endif
#include <cmath>

namespace mathex
{
#define _PI 3.14159265358979323846 // pi
  //#define _PI 4.0*atan(1.0)
  template<typename T>
  constexpr T PI{(T)_PI};
  template<typename T>
  constexpr T _2PI{(PI<T> * 2)};
  template<typename T>
  constexpr T halfPI{(PI<T> / (T)2)};

  template<typename T>
  struct size_tt // size_t is taken by stl
  {
    typedef T type;

    T width, height;

    size_tt()
        : width(0), height(0)
    {
    }

    size_tt(T w, T h)
        : width(w), height(h)
    {
    }
  };

  using iSize = size_tt<int>;
  using uiSize = size_tt<unsigned int>;
  using fSize = size_tt<float>;
  using dSize = size_tt<double>;

  template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
  T DegreeToRad(T degree)
  {
    return (T)((degree / (T)180) * (T)_PI);
  }

  template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
  T RadToDegree(T rad)
  {
    return (T)((rad / (T)_PI) * (T)180);
  }

  // available in std as of c++17
  template<typename T>
  const T& clamp(const T& v, const T& lo, const T& hi)
  {
    return std::max(std::min(v, hi), lo);
  }

  template<typename T>
  static inline bool fltEqual(const T left, const T right)
  {
    static_assert(std::is_floating_point<T>::value, "");
    return std::abs(left - right) <= std::numeric_limits<T>::epsilon();
  }
}
