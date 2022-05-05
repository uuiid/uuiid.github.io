#include <fstream>
#include <iostream>
#include <sstream>
#include <server/server.h>
#include <server/rpc_server.h>
#include <fmt/format.h>

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
    s.rpc_server_ptr_->register_fun_t("test_1", []() {
      std::cout << "call test_1" << std::endl;
    });
    auto test_value{"test value"s};
    s.rpc_server_ptr_->register_fun_t(
        "test_2",
        [=](const std::string& in_arg,
            const std::int32_t& in_int) {
          std::cout << "call test_2 " << test_value << std::endl;
        });
    s.rpc_server_ptr_->register_fun_t("test_3", [](const std::string& in_arg,
                                                   const std::int32_t& in_int) {
      std::cout << "call test_3 " << in_arg << " " << in_int << std::endl;
      return "test return "s;
    });
    s.rpc_server_ptr_->register_fun_t("test_4", []() {
      std::cout << "call test_4" << std::endl;
      return 1;
    });
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
