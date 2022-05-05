//
// Created by TD on 2022/4/29.
//

#include "rpc_server.h"
#include <server/server.h>
void rpc_server::register_fun(const std::string& in_name, const rpc_server::call_fun& in_call) {
  fun_list_.emplace(in_name, in_call);
}
rpc_reply rpc_server::operator()(const std::string& in_name,
                                 const std::optional<nlohmann::json>& in_parm) const {
  rpc_reply reply{};

  if (fun_list_.find(in_name) != fun_list_.end()) {
    reply.result = fun_list_.at(in_name)(in_parm);
  } else {
    reply.result = method_not_found;
  }
  return reply;
}
rpc_server::rpc_server()
    : fun_list_() {
}
rpc_server_ref::rpc_server_ref(std::weak_ptr<rpc_server> in_server,
                               std::function<void()> in_close_fun)
    : server(std::move(in_server)),
      fun_list_() {
  fun_list_.emplace("rpc.close", [=](const std::optional<nlohmann::json>&) -> rpc_reply {
    in_close_fun();
    return {};
  });
  in_server.lock()->register_fun_t("sda"s, []() -> std::int64_t {

    return {};

  });


}
rpc_reply rpc_server_ref::operator()(const std::string& in_name, const std::optional<nlohmann::json>& in_parm) const {
  rpc_reply reply{};
  if (fun_list_.find(in_name) != fun_list_.end()) {
    reply.result = fun_list_.at(in_name)(in_parm);
  } else {
    reply = (*server.lock())(in_name, in_parm);
  }
  return reply;
}
