#include <server.h>
#include <iostream>

void session::start() {
    do_read();
}

void session::do_read() {
    auto self{shared_from_this()};
    boost::asio::async_read(
            socket_,
            boost::asio::buffer(data_),
            [self, this](boost::system::error_code in_err,
                         std::size_t in_len) {
                if (!in_err) {
                    std::cout << "read " << std::endl;
                    this->do_write();
                } else {
                    std::cout << in_err.message() << std::endl;
                    socket_.close();
                }
            }
    );

}

void session::do_write() {
    auto self{shared_from_this()};
    boost::asio::async_write(
            socket_,
            boost::asio::buffer(data_),
            [self, this](boost::system::error_code in_err, std::size_t in_len) {
                if (!in_err) {
                    std::cout << "write " << std::endl;
                    this->do_read();
                } else {
                    std::cout << in_err.message() << std::endl;
                    socket_.close();
                }
            });
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
