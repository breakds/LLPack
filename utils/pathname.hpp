/*********************************************************************************
 * File: pathname.hpp
 * Description: *nix file system pathname utilities
 * by BreakDS, @ University of Wisconsin-Madison, Fri Jul 13 23:55:03 CDT 2012
 *********************************************************************************/

#pragma once

#include <vector>
#include <string>
#include "LLPack/utils/extio.hpp"

namespace path
{

  // build Triplet file list (FFFL) = Folder + Filename + postFix List
  template<typename listType>
  std::vector<std::string> FFFL( const std::string& folder, const listType& filelist, const std::string postfix="" )
  {
    std::vector<std::string> tmp;
    tmp.resize( filelist.size() );
    for ( int i=0; i<filelist.size(); i++ ) {
      tmp[i] = folder + "/" + static_cast<std::string>( filelist[i] ) + postfix;
    }
    return tmp;
  }

};
