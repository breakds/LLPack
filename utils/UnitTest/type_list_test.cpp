#include <cstdio>
#include <initializer_list>
#include <functional>
#include <tuple>
#include <map>
#include <iostream>
#include "../testing.hpp"
#include "../type_list.hpp"



int main() {
  // Callback<void,int,int> c([](int x, int y){
  //     printf("%d %d\n", x, y);
  //   },
  //   12,
  //   13);
  // c();

  unit_test::Tester tester;
  tester.RegisterTest("test1",
                      std::function<bool(int,char)> 
                      ([](int a, char c) {
                        printf("%d and %c\n", a, c);
                        return true;
                      }),
                      2, 'c');
  
  tester.RegisterTest("test2",
                      std::function<bool(bool,bool)> 
                      ([](bool x, bool y) {
                        return x && y;
                      }), 
                      {{true, true}, {true,false}, {false, true}, {false, false}});
                            
                          

  tester.Start();

  return 0;
}
