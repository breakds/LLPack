/*********************************************************************************
 * File: pathname.hpp
 * Description: *nix file system pathname utilities
 * by BreakDS, @ University of Wisconsin-Madison, Fri Jul 13 23:55:03 CDT 2012
 *********************************************************************************/

#include <string>
#include "LLPack/utils/extio.hpp"

namespace path
{

  // build Triplet file list (FFFL) = Folder + Filename + postFix List
  template<typename listType>
  vector<string> FFFL( const string& folder, const listType& filelist, const string postfix="" )
  {
    vector<string> tmp;
    tmp.resize( filelist.size() );
    for ( int i=0; i<filelist.size(); i++ ) {
      tmp[i] = folder + "/" + static_cast<string>( filelist[i] ) + postfix;
    }
    return tmp;
  }

};
