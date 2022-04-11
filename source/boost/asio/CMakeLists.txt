add_executable(uuid_boost_asio_server_test
        main_server.cpp
        server.h
        server.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )

target_link_libraries(uuid_boost_asio_server_test PUBLIC fmt::fmt)
target_include_directories(uuid_boost_asio_server_test PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(uuid_boost_asio_client_test
        main_client.cpp
        ../../win_exe.rc
        ../../uuiid.manifest)

target_link_libraries(uuid_boost_asio_client_test PUBLIC fmt::fmt)

target_compile_definitions(uuid_boost_asio_server_test PUBLIC _WIN32_WINNT=0x0A00)
target_compile_definitions(uuid_boost_asio_client_test PUBLIC _WIN32_WINNT=0x0A00)
add_test(NAME uuid_boost_asio_server_test_com COMMAND uuid_boost_asio_server_test "8442")
add_test(NAME uuid_boost_asio_client_test_com COMMAND uuid_boost_asio_client_test "127.0.0.1" "8442")
