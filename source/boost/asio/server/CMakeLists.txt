target_sources(
        uuid_boost_asio_server_test
        PUBLIC
        server.h
        session_manager.h
        parser_rpc.h
        exception/json_rpc_error.h
        rpc_server.h

        PRIVATE
        server.cpp
        session_manager.cpp
        parser_rpc.cpp
        rpc_server.cpp
)
