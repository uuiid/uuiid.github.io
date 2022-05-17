add_executable(uuiid_json
        main.cpp
        ../win_exe.rc
        ../uuiid.manifest
        )
target_link_libraries(uuiid_json PUBLIC fmt::fmt Boost::locale)
add_test(NAME uuiid_json_com COMMAND uuiid_json)
