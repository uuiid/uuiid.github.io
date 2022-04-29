//
// Created by TD on 2022/4/29.
//

#include "rpc_client.h"
std::string rpc_client::call_server(const std::string& in_string) {
  boost::asio::write(client_socket, boost::asio::buffer(in_string));
  std::string l_r{};
  boost::asio::read(client_socket, boost::asio::dynamic_buffer(l_r));
  return l_r;
}
