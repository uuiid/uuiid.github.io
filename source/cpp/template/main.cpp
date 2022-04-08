#include <variant>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <regex>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_set>
#include <variant>
#include <vector>

struct json
{
    template <typename T>
    void get_to(T &in_t) const
    {
    }
};

template <class... Types>
struct adl_t
{
    using var_t = std::variant<Types...>;
    using index_t = std::size_t;

    static void get_variant_value(const json &j,
                                  var_t &in_var,
                                  const index_t &in_index)
    {
        get_variant_value(j, in_var, in_index, std::index_sequence_for<Types...>{});
    }

    template <index_t... Index>
    static void get_variant_value(const json &j,
                                  var_t &in_var,
                                  const index_t &in_index,
                                  std::index_sequence<Index...>)
    {
        (((in_index == Index)
              ? (void)j.get_to(std::get<Index>(in_var))
              : void()),
         ...);
    }
};
int main(int argc, char const *argv[])
{
    json l_j{};
    std::variant<bool, std::int64_t, std::string> l_var{};
    adl_t<bool, std::int64_t, std::string>::get_variant_value(l_j, l_var, 2);
    return 0;
}
