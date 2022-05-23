add_executable(uuiid_std_move
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )
target_link_libraries(uuiid_std_move PUBLIC fmt::fmt Boost::locale)
add_test(NAME uuiid_std_move_com COMMAND uuiid_std_move "{:%H:%M:%S}")
