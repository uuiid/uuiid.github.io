#include <fstream>
#include <iostream>
#include <sstream>
#include <server/server.h>

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
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto){ io_context.stop(); });

        server s(io_context, port);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
