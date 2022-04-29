//
// Created by TD on 2022/4/29.
//

#pragma once
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>

#include <variant>
#include <optional>
#include <server/exception/json_rpc_error.h>

namespace detail {
// helper type for the visitor
template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
}  // namespace detail

class rpc_reply {
 private:
  friend void to_json(nlohmann::json& nlohmann_json_j, const rpc_reply& nlohmann_json_t) {
    nlohmann_json_j["jsonrpc"] = nlohmann_json_t.jsonrpc_;
    std::visit(detail::overloaded{
                   [&](const nlohmann::json& in_json) {
                     nlohmann_json_j["result"] = in_json;
                   },
                   [&](const rpc_error& in_error) {
                     nlohmann_json_j["error"] = in_error;
                   }},
               nlohmann_json_t.result);
    std::visit(detail::overloaded{
                   [&](const std::int64_t& in_id) {
                     nlohmann_json_j["id"] = in_id;
                   },
                   [&](const std::string& in_str_id) {
                     nlohmann_json_j["id"] = in_str_id;
                   },
                   [&](const std::monostate& in_null_id) {
                     nlohmann_json_j["id"] = nlohmann::json{nlohmann::json::value_t::null};
                   }},
               nlohmann_json_t.id_);
  }

 public:
  std::string jsonrpc_{};
  std::variant<nlohmann::json, rpc_error> result{};
  std::variant<std::int64_t, std::string, std::monostate> id_{};
  constexpr static const std::size_t err_index{1};
};
