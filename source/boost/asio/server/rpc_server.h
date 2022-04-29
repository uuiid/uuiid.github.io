//
// Created by TD on 2022/4/29.
//
#pragma once

#include <map>
#include <string>
#include <functional>
#include <server/exception/json_rpc_error.h>

template <typename... Args>
class rpc_server {
 public:
  std::map<std::string, std::function<void()>> fun_list_;
};
