#pragma once

#include <type_traits>
#include <string>
#include <initializer_list>
#include "extio.hpp"
#include "callback.hpp"
#include "type_list.hpp"

namespace unit_test {

  using namespace type_list;

  class Tester {
  public:

    Tester() {}
    
    template <typename... ArgTypes>
    void RegisterTest(const std::string &test_name,
                      std::function<bool(ArgTypes...)> test_func,
                      ArgTypes... args) {
      RegisterTest(test_name, test_func, {{args...}});
    }

    
    template <typename... ArgTypes>
    void RegisterTest(const std::string &test_name,
                      std::function<bool(ArgTypes...)> test_func,
                      std::initializer_list<std::vector<MultiTypeWrapper<ArgTypes...> > > args) {
      if (test_store_.find(test_name) != test_store_.end()) {
        Error("Duplicated Test Name \"%s\".", test_name.c_str());
        exit(-1);
      } 
      
      std::vector<std::function<bool()> > fun_q;
      for (auto& arg_case : args) {
        std::tuple<ArgTypes...> t = CreateTuple<ArgTypes...>(arg_case);
        Callback<bool, ArgTypes...> callback(test_func, t);
        fun_q.push_back([callback]() {
            return callback();
          });
      }
      
      test_store_.emplace(test_name, std::move(fun_q));
    }



    void Start() {
      auto iter = test_store_.begin();
      for (;iter != test_store_.end(); ++iter) {
        auto& fun_q = iter->second;
        int passed = 0;
        int current = 0;
        std::vector<int> failed_cases;
        for (auto& fun : fun_q) {
          if (fun()) {
            passed++;
          } else {
            failed_cases.push_back(current);
          }
          current++;
        }
        
        if (passed == current) {
          Done("%s passed. (%d/%d)", iter->first.c_str(), 
               passed, current);
        } else {
          Error("%s failed. (%d/%d)", iter->first.c_str(),
                passed, current);
          printf(" - failed cases are:");
          for (auto& id : failed_cases) {
            printf(" %d", id);
          }
          printf("\n");
        }
      }
    }

  private:
    std::map<std::string,std::vector<std::function<bool()> > > test_store_;
  };
}





