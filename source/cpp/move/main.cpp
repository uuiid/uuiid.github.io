//
// Created by TD on 2022/4/6.
//

#include <regex>
#include <string>
#include <iostream>
#include <boost/locale.hpp>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <chrono>
#include <locale>
#include <date/date.h>

class test_value {
 private:
  std::int32_t p_v{};

 public:
  explicit test_value(int32_t pV) : p_v(pV) {}
  virtual ~test_value() = default;
};

int main(int argc, char* argv[]) {
  test_value value{100};
  test_value* value_ptr{&value};
  auto l_test = std::move(value);
  std::cout << bool(value_ptr) << std::endl;
}
