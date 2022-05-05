//
// Created by TD on 2022/4/10.
//

#include <boost/asio.hpp>
#include <iostream>
#include <client/rpc_client.h>

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
