add_executable(uuid_boost_asio_test
        main_server.cpp
        server.h
        server.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )

target_link_libraries(uuid_boost_asio_test PUBLIC fmt::fmt)
target_include_directories(uuid_boost_asio_test PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_test(NAME uuid_boost_asio_test_com COMMAND uuid_boost_asio_test "8442")
