#pragma once

#include <algorithm>
#include <numeric>
#include <iterator>

// obsolete since c++ supports auto param in lambda
//#define DeclTypeFromItem(container) decltype(*std::begin(container))

namespace func
{
  // implementation of a basic identity class till there is c++20 support
  template<typename T>
  struct identity
  {
    constexpr T&& operator()(T&& t) const noexcept
    {
      return std::forward<T>(t);
    }
  };

  template<typename Tcontainer, typename Func>
  inline Tcontainer& for_each(Tcontainer& container, Func f)
  {
    std::for_each(container.begin(), container.end(), f);
    return container;
  }

  template<typename Tcontainer, typename Tcontainer2, typename Func>
  inline Tcontainer& for_each(Tcontainer& container, Tcontainer2& container2, Func f)
  {
    auto size = container.size();
    for(size_t i(0); i < size; ++i)
      f(container[i], container2[i]);
    return container;
  }

  template<typename Tcontainer, typename Func>
  inline Tcontainer& for_each_index(Tcontainer& container, Func f)
  {
    auto size = container.size();
    for(size_t i(0); i < size; ++i)
      f(container[i], i);
    return container;
  }

  template<typename Tcontainer, typename Func>
  inline bool all_of(Tcontainer& container, Func f)
  {
    return std::all_of(container.begin(), container.end(), f);
  }

  template<typename Tcontainer, typename Func>
  inline bool any_of(Tcontainer& container, Func f)
  {
    return std::any_of(container.begin(), container.end(), f);
  }

  template<typename Tcontainer, typename T>
  inline bool contains(Tcontainer& container, const T& value)
  {
    return (std::find(container.begin(), container.end(), value) != container.end());
  }

  template<typename TcontainerFrom, typename TcontainerTo, typename Func>
  inline TcontainerTo& transform(TcontainerFrom& containerFrom, TcontainerTo& containerTo, Func f)
  {
    std::transform(containerFrom.begin(), containerFrom.end(), containerTo.begin(), f);
    return containerTo;
  }

  template<typename TcontainerTo, typename TcontainerFrom, typename Func>
  inline TcontainerTo transform(TcontainerFrom& containerFrom, Func f)
  {
    TcontainerTo containerTo;
    std::transform(containerFrom.begin(), containerFrom.end(), std::back_inserter(containerTo), f);
    return containerTo;
  }

  template<typename TcontainerFrom, typename TcontainerFrom2, typename TcontainerTo, typename Func>
  inline TcontainerTo& transform(TcontainerFrom& containerFrom, TcontainerFrom2 containerFrom2, TcontainerTo& containerTo, Func f)
  {
    std::transform(containerFrom.begin(), containerFrom.end(), containerFrom2.begin(), containerTo.begin(), f);
    return containerTo;
  }

  template<class T>
  using add_const_lvalue_reference_t = std::add_lvalue_reference_t<std::add_const_t<T>>;
}