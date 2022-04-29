//
// Created by TD on 2022/4/29.
//

#pragma once

#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>

#include <variant>
#include <optional>
#include <server/exception/json_rpc_error.h>
#include <server/rpc_reply.h>
using namespace std::literals;
class rpc_request {
 private:
  //  NLOHMANN_DEFINE_TYPE_INTRUSIVE(rpc_request, jsonrpc_);
  //  friend void to_json(nlohmann::json& nlohmann_json_j, const rpc_request& nlohmann_json_t) {
  //  }
  friend void from_json(const nlohmann::json& nlohmann_json_j, rpc_request& nlohmann_json_t) {
    nlohmann_json_j.at("jsonrpc").get_to(nlohmann_json_t.jsonrpc_);
    nlohmann_json_j.at("method").get_to(nlohmann_json_t.method_);
    if (nlohmann_json_j.contains("id")) {
      auto&& l_j = nlohmann_json_j.at("id");
      if (l_j.is_number())
        nlohmann_json_t.id_ = l_j.get<std::int64_t>();
      else if (l_j.is_string())
        nlohmann_json_t.id_ = l_j.get<std::string>();
      else
        throw internal_error_exception{};
    } else {
      nlohmann_json_t.is_notice = true;
    }

    if (nlohmann_json_j.contains("params"))
      nlohmann_json_t.params_ = nlohmann_json_j.at("params");
  }

 public:
  bool is_notice{};
  std::string jsonrpc_{};
  std::string method_{};
  std::optional<nlohmann::json> params_{};
  std::variant<std::int64_t, std::string, std::monostate> id_{0};
};
class rpc_server;
class parser_rpc {
 private:
  std::string json_data_{};

  static std::optional<rpc_reply> call_one(const rpc_request& in_request,
                     const rpc_server& in_server);

 public:
  explicit parser_rpc(std::string string)
      : json_data_(std::move(string)) {}

  std::string operator()(const rpc_server& in_server);
};
