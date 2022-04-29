//
// Created by TD on 2022/4/29.
//
#pragma once

#include <map>
#include <string>
#include <functional>
#include <optional>
#include <server/exception/json_rpc_error.h>
#include <server/rpc_reply.h>

class rpc_server {
 public:
  using call_fun = std::function<rpc_reply(const std::optional<nlohmann::json>&)>;
  std::map<std::string,
           call_fun>
      fun_list_{};
  rpc_server() = default;
  void register_fun(const std::string& in_name, const call_fun& in_call);

  rpc_reply operator()(const std::string& in_name,
                       const std::optional<nlohmann::json>& in_parm) const;
};
