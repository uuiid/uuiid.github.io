#include <fstream>
#include <iostream>
#include <sstream>
#include <server.h>

#include <fmt/format.h>

int main(int argc, char *argv[])
{
    try
    {
        std::uint16_t port{0};
        if (argc == 2)
        {
            port = std::atoi(argv[1]);
        }

        boost::asio::io_context io_context;

        server s(io_context, port);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
