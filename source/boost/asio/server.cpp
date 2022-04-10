#include <server.h>

void session::start()
{
    do_read();
}

void session::do_read()
{
    auto self{shared_from_this()};

    socket_.async_read_some(
        boost::asio::buffer(data_),
        [self](boost::system::error_code in_err,
               std::size_t in_len)
        {
            if (!in_err)
            {
                self->do_write();
            }
        });
}
void session::do_write()
{
    auto self{shared_from_this()};
    data_ += "ok";
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(data_),
        [self](boost::system::error_code in_err, std::size_t in_len)
        {
            if (!in_err)
            {
//                self->do_read();
            }
        });
}

void server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code in_err, boost::asio::ip::tcp::socket &in_socket)
        {
            if (!in_err)
            {
                std::make_shared<session>(std::move(in_socket))->start();
            }
            this->do_accept();
        });
}
