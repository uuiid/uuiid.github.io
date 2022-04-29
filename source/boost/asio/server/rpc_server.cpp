//
// Created by TD on 2022/4/29.
//

#include "rpc_server.h"
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
