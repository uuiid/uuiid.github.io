#include <server/server.h>
#include <iostream>

#include <server/parser_rpc.h>
#include <nlohmann/json.hpp>
server::server(boost::asio::io_context &in_io_context,
               std::uint16_t in_port)
    : acceptor_(in_io_context,
                boost::asio::ip::tcp::endpoint{
                    boost::asio::ip::address::from_string("127.0.0.1"), in_port}) {
  do_accept();
}

session::session(boost::asio::ip::tcp::socket in_socket)
    : socket_(std::move(in_socket)),
      data_(std::size_t(8192), '\0'){

      };

void session::start() {
  do_read();
}

void session::do_read() {
  static std::string l_delim{};
  /// 确保json字符串完全读取完整
  boost::asio::async_read(
      socket_,
      boost::asio::buffer(data_),
      [&](
          // 最新 async_read_some 操作的结果。
          const boost ::system ::error_code &error,
          // 到目前为止传输的字节数
          std ::size_t bytes_transferred) -> std::size_t {
        if (!error) {
          if (nlohmann::json::accept(data_))
            return 0;
          else
            return data_.size() - bytes_transferred;
        }
        return 0;
      },
      [self = shared_from_this(), this](boost::system::error_code in_err,
                                        std::size_t in_len) {
        if (!in_err) {
          self->parser_rpc_ptr = std::make_shared<parser_rpc>(data_.substr(0, in_len));
          this->do_write();
        } else {
          std::cout << "read err " << in_err.message() << std::endl;
          socket_.close();
        }
      });
  //  socket_.async_read_some(
  //      boost::asio::buffer(data_),
  //      [self = shared_from_this(), this](boost::system::error_code in_err,
  //                                        std::size_t in_len) {
  //        if (!in_err) {
  //          std::cout << "read " << data_.substr(0, in_len) << std::endl;
  //          this->do_write();
  //        } else {
  //          std::cout << "read err " << in_err.message() << std::endl;
  //          socket_.close();
  //        }
  //      });
}

void session::do_write() {
  boost::asio::async_write(
      socket_,
      boost::asio::buffer(msg_),
      [self = shared_from_this(), this, ](boost::system::error_code in_err, std::size_t in_len_) {
        if (!in_err) {
          std::cout << "write " << data_ << std::endl;
          this->do_read();
        } else {
          std::cout << "write err " << in_err.message() << std::endl;
        }
        socket_.close();
      });
  //    socket_.async_write_some(
  //            boost::asio::buffer(msg_),
  //            [self = shared_from_this(), this, in_len](boost::system::error_code in_err, std::size_t in_len_) {
  //
  //                if (!in_err) {
  //                    std::cout << "write " << data_.substr(0, in_len) << std::endl;
  //                    this->do_read();
  //                } else {
  //                    std::cout << "write err " << in_err.message() << std::endl;
  //                }
  //                socket_.close();
  //            });
}
void session::stop() {
  socket_.close();
}

void server::do_accept() {
  acceptor_.async_accept(
      [this](boost::system::error_code in_err, boost::asio::ip::tcp::socket &in_socket) {
        if (!in_err) {
          std::make_shared<session>(std::move(in_socket))->start();
        }
        this->do_accept();
      });
}
