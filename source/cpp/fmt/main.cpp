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

int main(int argc, char *argv[]) {
  if (argc == 2) {
    auto l_t = std::chrono::hours{3} + std::chrono::minutes{2} +
               std::chrono::seconds{1} + std::chrono::milliseconds{58};
    auto l_str = fmt::format(argv[1], l_t);
    std::cout << l_str << std::endl;
  }
  return 1;
}
