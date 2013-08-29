#pragma once

#include <vector>
#include <tuple>

namespace type_list {


  // MultiTypeWrapper
  
  template <typename... tlist>
  class MultiTypeWrapper {
  };

  template <typename H>
  class MultiTypeWrapper<H> {
  public:
    MultiTypeWrapper() {}
    
    MultiTypeWrapper(const H &value) : value_(value) {}

    operator H () const {
      return value_;
    }
  private:
    H value_;
  };

  template <typename H, typename... T>
  class MultiTypeWrapper<H, T...> 
    : public MultiTypeWrapper<T...> {
  
  public:
    MultiTypeWrapper() {}
    
    MultiTypeWrapper(const H &value) : value_(value) {}
    
    template <typename C>
    MultiTypeWrapper(const C &value) : MultiTypeWrapper<T...>(value) {}

    operator H () const {
      return value_;
    }
  private:
    H value_;
  };
  

  // CreateTuple from intializer_list


  namespace {
    template <int ind, typename... T>
    class CreateTupleHelper {
    public:
      static inline void SetSlot(std::tuple<T...> &t, 
                                 const std::vector<MultiTypeWrapper<T...> >& v) {
        std::get<ind>(t) = 
          static_cast<typename std::tuple_element<ind, std::tuple<T...> >::type>(v[ind]);
        CreateTupleHelper<ind-1, T...>::SetSlot(t, v);
      }
    };
    
    template <typename... T>
    class CreateTupleHelper<0, T...> {
    public:
      static inline void SetSlot(std::tuple<T...> &t,
                                 const std::vector<MultiTypeWrapper<T...> >& v) {
        std::get<0>(t) = 
          static_cast<typename std::tuple_element<0, std::tuple<T...> >::type>(v[0]);
      }
    };
      
  }


  template <typename... T>
  std::tuple<T...> CreateTuple(std::vector<MultiTypeWrapper<T...> > init_list) {
    std::tuple<T...> t;
    CreateTupleHelper<sizeof...(T)-1, T...>::SetSlot(t, init_list);
    return t;
  }
  

    // // class-like functor length
    // template <typename... tlist>
    // class length {
    // public:
    //   enum { value = 0 };
    // };

    // template <typename T>
    // class length<T> {
    // public:
    //   enum { value = 1 };
    // };

    // template <typename H, typename... L>
    // class length<H, L...> {
    // public:
    //   enum { value = length<L...>::value + 1 };
    // };
  }
