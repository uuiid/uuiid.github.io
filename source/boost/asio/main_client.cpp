//
// Created by TD on 2022/4/10.
//

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

enum { max_length = 1024 };
int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

        std::cout << "Enter message: ";
        char request[] = "test";
        size_t request_length = std::strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        size_t reply_length = boost::asio::read(s,
                                                boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
