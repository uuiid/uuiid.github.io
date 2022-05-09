//
// Created by TD on 2022/4/10.
//

#include <boost/asio.hpp>
#include <iostream>
#include <client/rpc_client.h>
#include <server/json_rpc_macro.h>

using boost::asio::ip::tcp;

class rpc_client_test : public rpc_client {
 public:
  using rpc_client::rpc_client;
  void test_1() {
    this->call_fun<false, void>("test_1"s);
  };
  void test_2(const std::string& in_arg,
              const std::int32_t& in_int) {
    this->call_fun<false, void>("test_2"s, in_arg, in_int);
  };
  std::string test_3(const std::string& in_arg,
                     const std::int32_t& in_int) {
    return this->call_fun<false, std::string>("test_3"s, in_arg, in_int);
  };
  std::int32_t test_4() {
    return this->call_fun<false, std::int32_t>("test_4"s);
  };
};

class rpc_client_sub : public rpc_client {
 public:
  using rpc_client::rpc_client;
};

#define DOODLE_RPC_FUN_DECLARATION_SUB(r, data, elem)       \
  DOODLE_RPC_GET_FUN_RETURN(elem)                           \
  DOODLE_RPC_GET_FUN_NAME(elem)                             \
  (DOODLE_RPC_TO_ARG(elem)) {                               \
    return this->call_fun<false,                            \
                          DOODLE_RPC_GET_FUN_RETURN(elem)>( \
        DOODLE_RPC_GET_FUN_NAME_STR(elem),                  \
        DOODLE_RPC_TO_ARG2(elem));                          \
  }

#define DOODLE_RPC_DECLARATION_SUB(rpc_server_name, ...)                                            \
  class rpc_server_name : public rpc_client {                                                       \
   public:                                                                                          \
    using rpc_client::rpc_client;                                                                   \
                                                                                                    \
    BOOST_PP_SEQ_FOR_EACH(DOODLE_RPC_FUN_DECLARATION_SUB, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
  };


int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }
    boost::asio::io_context io_context;
    rpc_client_test l_c{io_context, argv[1], (std::uint16_t)std::atoi(argv[2])};

    l_c.test_1();
    l_c.test_2("rpc_client_test 2"s, 2);
    l_c.test_3("rpc_client_test 3"s, 3);
    l_c.test_4();

  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
