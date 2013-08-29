// Callback functions
// Author: BreakDS <breakds@gmail.com>
// 
// This file provides implementation of a callback wrapper class

#pragma once

#include "sequence.hpp"

template <typename ReturnType, typename... ArgTypes>
class Callback {
public:
  Callback(std::function<ReturnType(ArgTypes...)> f,
           ArgTypes... args) 
    : f_(f), args_(std::make_tuple(args...)) {}

  Callback(std::function<ReturnType(ArgTypes...)> f,
           const std::tuple<ArgTypes...> &args) 
    : f_(f), args_(args) {}

  Callback(const Callback& other) : f_(other.f_), args_(other.args_) {}

  ReturnType operator()() const{
    return Execute(typename sequence::NatNumSeq<sizeof...(ArgTypes)-1>::type());
  }

private:
  template <int... S>
  inline ReturnType Execute(sequence::seq<S...>) const {
    return f_(std::get<S>(args_)...);
  }

private:
  std::function<ReturnType(ArgTypes...)> f_;
  std::tuple<ArgTypes...> args_;
};


