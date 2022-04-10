add_executable(uuid_boost_asio_test
        main.cpp
        server.h
        server.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )

target_link_libraries(uuid_boost_asio_test PUBLIC fmt::fmt)
add_test(NAME uuid_boost_asio_test_com COMMAND uuid_boost_asio_test "test_args_${CMAKE_CURRENT_LIST_DIR}")
