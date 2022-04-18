//
// Created by TD on 2022/4/6.
//

#include <regex>
#include <string>
#include <iostream>
#include <boost/locale.hpp>

int main(int argc, char *argv[]) {
  if (argc == 3) {
    try {
      std::wstring l_reg{boost::locale::conv::utf_to_utf<wchar_t>(argv[1])};
      std::wstring l_str{boost::locale::conv::utf_to_utf<wchar_t>(argv[2])};
      std::wregex regex{l_reg};
      std::wsmatch smatch{};
      if (std::regex_match(l_str,
                           smatch,
                           regex)) {
        for (auto &&i : smatch) {
          std::cout << boost::locale::conv::utf_to_utf<char>(i.str()) << std::endl;
        }
      } else {
        std::cout << "not match " << boost::locale::conv::utf_to_utf<char>(l_str) << std::endl;
      }
    } catch (const std::runtime_error &error) {
      std::cout << error.what() << std::endl;
    }
    return 0;
  }
  return 1;
}
