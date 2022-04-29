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

 private:
  std::map<std::string,
           call_fun>
      fun_list_{};

 public:
  rpc_server();
  void register_fun(const std::string& in_name, const call_fun& in_call);

  rpc_reply operator()(const std::string& in_name,
                       const std::optional<nlohmann::json>& in_parm) const;
};
class session;
class rpc_server_ref {
 public:
  using call_fun = std::function<rpc_reply(const std::optional<nlohmann::json>&)>;

 private:
  std::map<std::string,
           call_fun>
      fun_list_{};

  std::weak_ptr<rpc_server> server;

 public:
  explicit rpc_server_ref(std::weak_ptr<rpc_server> in_server,
                          std::function<void()> in_close_fun);
  rpc_reply operator()(const std::string& in_name,
                       const std::optional<nlohmann::json>& in_parm) const;
};
