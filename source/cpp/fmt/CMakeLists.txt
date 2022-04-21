add_executable(uuiid_std_fmt
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )
target_link_libraries(uuiid_std_fmt PUBLIC fmt::fmt Boost::locale)
add_test(NAME uuiid_std_fmt_com COMMAND uuiid_std_fmt "{:%H:%M:%S}")
