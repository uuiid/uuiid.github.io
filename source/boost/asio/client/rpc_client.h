//
// Created by TD on 2022/4/29.
//

#pragma once
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include <server/rpc_reply.h>
#include <server/exception/json_rpc_error.h>
#include <server/parser_rpc.h>

class fun_stub {
 public:
  constexpr static std::string_view method_{"s"};
  using Args   = std::tuple<const std::string&, const std::string&>;
  using Result = std::string;
};

class rpc_client {
  boost::asio::ip::tcp::socket client_socket;

  class close {
   public:
    constexpr static std::string_view method_{"rpc.close"};
    using Args   = std::tuple<>;
    using Result = void;
  };

 public:
  rpc_client(boost::asio::io_context& in_context,
             const std::string& in_host,
             std::uint16_t in_post)
      : client_socket(in_context,
                      boost::asio::ip::tcp::endpoint{
                          boost::asio::ip::address::from_string(in_host),
                          in_post}){};

 protected:
  std::string call_server(const std::string& in_string);

  template <typename FunType>
  auto call_fun(typename FunType::Args args) -> typename FunType::Result {
    nlohmann::json l_json{};

    rpc_request l_rpc_request{};
    l_rpc_request.method_ = std::string{FunType::method_};
    if constexpr (std::tuple_size<typename FunType::Args>::value > 0) {
      l_rpc_request.params_ = std::apply(FunType::to_json, args);
    }
    l_json             = l_rpc_request;
    nlohmann::json l_r = nlohmann::json::parse(call_server(l_json.dump()));
    auto l_rpc_r       = l_r.template get<rpc_reply>();
    if (l_rpc_r.result.index() != rpc_reply::err_index) {
      if constexpr (std::is_same_v<void, typename FunType::Result>)
        return void();
      else
        return std::get<nlohmann::json>(l_rpc_r.result).template get<typename FunType::Result>();
    } else {
      auto l_err_ = std::get<rpc_error>(l_rpc_r.result);
      l_err_.to_throw();
    }
  }
};
