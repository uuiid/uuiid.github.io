#include <server/server.h>
#include <iostream>

#include <server/parser_rpc.h>
#include <server/rpc_server.h>
#include <server/session_manager.h>
#include <nlohmann/json.hpp>
#include <utility>
server::server(boost::asio::io_context &in_io_context,
               std::uint16_t in_port)
    : acceptor_(in_io_context,
                boost::asio::ip::tcp::endpoint{
                    boost::asio::ip::address::from_string("127.0.0.1"), in_port}),
      rpc_server_ptr_(std::make_shared<rpc_server>()),
      session_manager_ptr(std::make_shared<session_manager>()) {
  do_accept();
}
void server::do_accept() {
  acceptor_.async_accept(
      [this](boost::system::error_code in_err, boost::asio::ip::tcp::socket &in_socket) {
        if (!in_err) {
          auto l_session = std::make_shared<session>(std::move(in_socket));
          session_manager_ptr->start(
              l_session,
              std::make_shared<rpc_server_ref>(
                  rpc_server_ptr_,
                  [=, se_wptr = l_session->weak_from_this()]() {
                    session_manager_ptr->stop(se_wptr.lock());
                  }));
        }
        this->do_accept();
      });
}

session::session(boost::asio::ip::tcp::socket in_socket)
    : socket_(std::move(in_socket)),
      data_(std::size_t(8192), '\0'),
      rpc_server_(){

      };

void session::start(std::shared_ptr<rpc_server_ref> in_server) {
  rpc_server_ = std::move(in_server);
  do_read();
}

void session::do_read() {
  static std::string l_delim{};
  /// 确保json字符串完全读取完整
  boost::asio::async_read(
      socket_,
      boost::asio::buffer(data_),
      "\r\n",
      [self = shared_from_this(), this](boost::system::error_code in_err,
                                        std::size_t in_len) {
        if (!in_err) {
          parser_rpc_ptr = std::make_shared<parser_rpc>(data_.substr(0, in_len));
          msg_           = (*parser_rpc_ptr)(*rpc_server_);
          this->do_write();
        } else {
          std::cout << "read err " << in_err.message() << std::endl;
          socket_.close();
        }
      });
}

void session::do_write() {
  if (socket_.is_open()) {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(msg_),
        [self = shared_from_this(), this](boost::system::error_code in_err, std::size_t in_len_) {
          if (!in_err) {
            this->do_read();
          } else {
            std::cout << "write err " << in_err.message() << std::endl;
            socket_.close();
          }
        });
  }
}
void session::stop() {
  socket_.close();
}
