target_sources(
        uuid_boost_asio_server_test
        PUBLIC
        server.h
        session_manager.h
        parser_rpc.h
        exception/json_rpc_error.h
        rpc_server.h
        rpc_reply.h

        PRIVATE
        server.cpp
        session_manager.cpp
        parser_rpc.cpp
        rpc_server.cpp
        rpc_reply.cpp
)

target_sources(
        uuid_boost_asio_client_test
        PUBLIC
        server.h
        session_manager.h
        parser_rpc.h
        exception/json_rpc_error.h
        rpc_server.h
        rpc_reply.h

        PRIVATE
        server.cpp
        session_manager.cpp
        parser_rpc.cpp
        rpc_server.cpp
        rpc_reply.cpp
)
