#include <fstream>
#include <iostream>
#include <sstream>
#include <server/server.h>
#include <server/rpc_server.h>
#include <fmt/format.h>

#include <boost/preprocessor.hpp>

class rpc_server_name : public rpc_server {
 public:
  using rpc_server::rpc_server;
  void init_register() override {
    register_fun_t("test_1", []() {
      std::cout << "call test_1" << std::endl;
    });
    register_fun_t(
        "test_2",
        [](const std::string& in_arg,
           const std::int32_t& in_int) {
          auto test_value{"test value"s};
          std::cout << "call test_2 " << test_value << std::endl;
        });
    register_fun_t("test_3", [](const std::string& in_arg,
                                const std::int32_t& in_int) {
      std::cout << "call test_3 " << in_arg << " " << in_int << std::endl;
      return "test return "s;
    });
    register_fun_t("test_4", []() {
      std::cout << "call test_4" << std::endl;
      return 1;
    });
    //    register_fun_t("t"s, &rpc_server_name::test_bind);
    register_fun_t("test_5", std::bind(&rpc_server_name::test_bind, this, std::placeholders::_1));
  }

  virtual std::string test_bind(const std::string& in_str) = 0;
};

#define DOODLE_RPC_GET_FUN_NAME_STR(list) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, list))
#define DOODLE_RPC_GET_FUN_NAME(list) BOOST_PP_TUPLE_ELEM(1, list)
#define DOODLE_RPC_GET_FUN_RETURN(list) BOOST_PP_TUPLE_ELEM(0, list)
#define DOODLE_RPC_TO_ARG_DEF(elem) BOOST_PP_TUPLE_ELEM(2, elem) arg
#define DOODLE_RPC_TO_ARG(list) BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(list), 3), DOODLE_RPC_TO_ARG_DEF(list), BOOST_PP_EMPTY())
#define DOODLE_RPC_TO_ARG2(list) BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(list), 3), arg, BOOST_PP_EMPTY())
#define DOODLE_RPC_FUN_DECLARATION(r, data, elem) \
  virtual DOODLE_RPC_GET_FUN_RETURN(elem) DOODLE_RPC_GET_FUN_NAME(elem)(DOODLE_RPC_TO_ARG(elem)) = 0;

#define DOODLE_RPC_CALL_FUN(r, data, elem)                                               \
  register_fun_t(DOODLE_RPC_GET_FUN_NAME_STR(elem),                                      \
                 [this](DOODLE_RPC_TO_ARG(elem)) -> DOODLE_RPC_GET_FUN_RETURN(elem) {        \
                   return this->DOODLE_RPC_GET_FUN_NAME(elem)(DOODLE_RPC_TO_ARG2(elem)); \
                 });

#define DOODLE_RPC_DECLARATION(rpc_server_name, ...)                                            \
  class rpc_server_name : public rpc_server {                                                   \
   public:                                                                                      \
    using rpc_server::rpc_server;                                                               \
    void init_register() override {                                                             \
      BOOST_PP_SEQ_FOR_EACH(DOODLE_RPC_CALL_FUN, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__));     \
    }                                                                                           \
    BOOST_PP_SEQ_FOR_EACH(DOODLE_RPC_FUN_DECLARATION, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
  };

DOODLE_RPC_DECLARATION(rpc_test_mar,
                       (void, test_1),
                       (void, test_2, const std::string&),
                       (std::string, test_3, const std::int32_t&))

class rpc_server_name2 : public rpc_server {
 public:
  using rpc_server::rpc_server;
  void init_register() override {
    void test(){};
  };

  int main(int argc, char* argv[]) {
    try {
      std::uint16_t port{0};
      if (argc == 2) {
        port = std::atoi(argv[1]);
      }

      boost::asio::io_context io_context;
      boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
      signals.async_wait([&](auto, auto) { io_context.stop(); });

      server s(io_context, port);

      io_context.run();
    } catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
  }
