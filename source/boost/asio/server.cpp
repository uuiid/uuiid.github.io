#include <server.h>

void server::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code in_err, boost::asio::ip::tcp::socket &in_socket)
        {
            if (!in_err)
            {
                std::make_shared<session>(std::move(in_socket));
            }
            this->do_accept();
        });
}