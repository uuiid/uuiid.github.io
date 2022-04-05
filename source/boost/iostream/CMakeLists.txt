add_executable(uuid_boost_iostream_test
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )

target_link_libraries(uuid_boost_iostream_test PUBLIC Boost::iostreams fmt::fmt)
