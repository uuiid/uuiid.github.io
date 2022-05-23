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
  test_value(test_value &&in_) noexcept {
    p_v     = in_.p_v;
    in_.p_v = 0;
  };
  test_value &operator=(test_value &&in_) noexcept {
    p_v     = in_.p_v;
    in_.p_v = 0;
    return *this;
  };
  /**
   * @brief 删除复制函数
   */
  test_value(test_value &) noexcept            = delete;
  /**
   * @brief 删除复制函数
   */
  test_value &operator=(test_value &) noexcept = delete;

  std::int32_t val() { return p_v; }
};

int main(int argc, char *argv[]) {
  test_value value{100};
  test_value *value_ptr{&value};
  auto l_test = std::move(value);
  std::cout << l_test.val() << std::endl;
}
