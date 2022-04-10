#pragma once

#include <boost/asio.hpp>

class session : public std::enable_shared_from_this<session>
{
    boost::asio::ip::tcp::socket socket_;

public:
    explicit session(boost::asio::ip::tcp::socket in_socket)
        : socket_(std::move(in_socket)){

          };
};

class server
{
    boost::asio::ip::tcp::acceptor acceptor_;

public:
    explicit server(boost::asio::io_context &in_io_context,
                    std::int16_t in_port)
        : acceptor_(in_io_context, boost::asio::ip::tcp::endpoint{boost::asio::ip::tcp::v6(), in_port})
    {
        do_accept();
    };

private:
    void do_accept();
};