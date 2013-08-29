// Wrapper for integer sequences
// Author: BreakDS <breakds@gmail.com>
// 
// This file defines constant integer squence (as in template
// arguments) and some wrapper classes.

#pragma once

namespace sequence {
  // define integer sequence
  template <int...>
  struct seq {};

  // define natrual number sequences
  // note that NatNumSeq<n>::type = seq<0,1,2,...,n>
  template <int H, int... T>
  struct NatNumSeq : NatNumSeq<H-1,H,T...> {};

  template <int... T>
  struct NatNumSeq<0, T...> {
    typedef seq<0, T...> type;
  };
}

