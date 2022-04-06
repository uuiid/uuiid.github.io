//
// Created by TD on 2022/4/6.
//

#include <regex>
#include <string>
#include <iostream>


int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string l_reg{argv[1]};
        std::string l_str{argv[2]};
        std::regex regex{l_reg};
        std::smatch smatch{};
        if (std::regex_match(l_str,
                             smatch,
                             regex)) {
            for (auto &&i: smatch) {
                std::cout << i.str() << std::endl;
            }
        } else {
            std::cout << "not match" << std::endl;
        }
        return 0;
    }
    return 1;
}
