//
// Created by TD on 2022/4/29.
//

#pragma once

#include <nlohmann/json.hpp>

#include <exception>
using namespace std::literals;

class parse_error_exception : public std::runtime_error {
 public:
  parse_error_exception() : std::runtime_error("Parse error语法解析错误"s) {}
};
class invalid_request_exception : public std::runtime_error {
 public:
  invalid_request_exception() : std::runtime_error("Invalid Request无效请求"s) {}
};
class method_not_found_exception : public std::runtime_error {
 public:
  method_not_found_exception() : std::runtime_error("Method not found找不到方法"s) {}
};
class invalid_params_exception : public std::runtime_error {
 public:
  invalid_params_exception() : std::runtime_error("Invalid params无效的参数"s) {}
};
class internal_error_exception : public std::runtime_error {
 public:
  internal_error_exception() : std::runtime_error("Internal error内部错误"s) {}
};

class rpc_error {
 private:
  friend void to_json(nlohmann::json& nlohmann_json_j, const rpc_error& nlohmann_json_t) {
    nlohmann_json_j["code"]    = nlohmann_json_t.code;
    nlohmann_json_j["message"] = nlohmann_json_t.message;
    nlohmann_json_j["data"]    = nlohmann_json_t.data;
  }
  friend void from_json(const nlohmann::json& nlohmann_json_j, rpc_error& nlohmann_json_t) {
    nlohmann_json_j.at("code").get_to(nlohmann_json_t.code);
    nlohmann_json_j.at("message").get_to(nlohmann_json_t.message);
    nlohmann_json_j.at("data").get_to(nlohmann_json_t.data);
  }

 public:
  constexpr rpc_error() = default;

  explicit rpc_error(std::int64_t in_code,
                     std::string in_message,
                     std::string in_data)
      : code(in_code),
        message(std::move(in_message)),
        data(std::move(in_data)) {}
  std::int64_t code{};
  std::string message{};
  std::string data{};

  void to_throw() {
  }
};
inline const static rpc_error parse_error{-32700, "Parse error语法解析错误"s, "服务端接收到无效的json 该错误发送于服务器尝试解析json文本"s};
inline const static rpc_error invalid_request{-32600, "Invalid Request无效请求"s, "发送的json不是一个有效的请求对象"s};
inline const static rpc_error method_not_found{-32601, "Method not found找不到方法"s, "该方法不存在或无效"s};
inline const static rpc_error invalid_params{-32602, "Invalid params无效的参数"s, "无效的方法参数"s};
inline const static rpc_error internal_error{-32603, "Internal error内部错误"s, "JSON-RPC内部错误"s};
