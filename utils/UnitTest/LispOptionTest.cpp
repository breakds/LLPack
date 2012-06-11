/*********************************************************************************
 * File: LispOptionTest.cpp
 * Description: Unit Test for LispFormParser.hpp
 * by BreakDS, Wed Jun  6 14:06:00 CDT 2012
 *********************************************************************************/

#include "../LispFormParser.hpp"

int main() {
  LispFormParser env;
  env.parse( "option.txt" );

  printf( "%d\n", env["list"]["option1"].toInt() );
  
  return 0;
}
