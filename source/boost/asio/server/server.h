#pragma once

#include <boost/asio.hpp>

class parser_rpc;

class session : public std::enable_shared_from_this<session> {
  boost::asio::ip::tcp::socket socket_;
  std::shared_ptr<parser_rpc> parser_rpc_ptr;

 public:
  explicit session(boost::asio::ip::tcp::socket in_socket);

  void start();
  void stop();

 private:
  void do_read();

  void do_write();

  std::string data_{};
  std::string msg_{};
};
class server {
  boost::asio::ip::tcp::acceptor acceptor_;

 public:
  explicit server(boost::asio::io_context &in_io_context,
                  std::uint16_t in_port);

 private:
  void do_accept();
};
