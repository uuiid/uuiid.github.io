//
// Created by TD on 2022/5/16.
//
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using namespace std::literals;
class test_obj {
 private:
  std::string test{"adasdsa"s};
  std::int64_t l_int{321};

 private:
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(test_obj, test, l_int);
};

int main(int argc, char *argv[]) {
  {  // json 初始化
    std::cout << nlohmann::json{"test"s}.dump() << std::endl;
  }
  {
    nlohmann::json j = "dsad"s;
    std::cout << j.dump() << std::endl;
  }
  {
    nlohmann::json j = test_obj{};
    std::cout << j.dump() << std::endl;
  }
  {
    std::cout << nlohmann::json{test_obj{}}.dump() << std::endl;
  }
  {
    auto l_obj = test_obj{};
    std::cout << nlohmann::json::object(l_obj).dump() << std::endl;
  }
}
