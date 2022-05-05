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
  }
};

#define DOODLE_RPC_FUN_ARGS(args_type,args_name) args_type,args_name


#define DOODLE_RPC_FUN_ARGS_VAR_MAP(r, data, i, elem) data(elem)

#define DOODLE_RPC_FUN_REGISTER(return_value, fun_name, ...)        \
  register_fun_t(                                                   \
      BOOST_PP_STRINGIZE(fun_name),                                 \
                         [this](                                    \
                            BOOST_PP_SEQ_FOR_EACH_I(DOODLE_RPC_FUN_ARGS_VAR_MAP,DOODLE_RPC_FUN_ARGS, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
                              ) -> return_value {      \
                           return BOOST_PP_CAT(this->, fun_name)(); \
                         });

#define DOODLE_RPC_FUN_DECLARATION(return_value, fun_name, ...) \
  virtual return_value fun_name(__VA_ARGS__) = 0;

#define DOODLE_VAR_MAP(r, data, i, elem) BOOST_PP_CAT(data, elem)

#define DOODLE_RPC_SUB(rpc_server_name, ...)                                                                      \
  class rpc_server_name : public rpc_server {                                                                     \
   public:                                                                                                        \
    using rpc_server::rpc_server;                                                                                 \
    void init_register() override {                                                                               \
      BOOST_PP_SEQ_FOR_EACH_I(DOODLE_VAR_MAP, DOODLE_RPC_FUN_REGISTER, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))      \
    }                                                                                                              \
    BOOST_PP_SEQ_FOR_EACH_I(DOODLE_VAR_MAP, DOODLE_RPC_FUN_DECLARATION, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))     \
};

// DOODLE_RPC_SUB(rpc_test_mar, (void, test_1, ), (void, test_2, ))
//DOODLE_RPC_SUB(rpc_test_mar, (void, test_1 ,()), (void, test_2 ,()))

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
