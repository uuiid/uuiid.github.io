add_executable(uuiid_std_regex
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )
target_link_libraries(uuiid_std_regex PUBLIC fmt::fmt)
add_test(NAME uuiid_std_regex_com COMMAND uuiid_std_regex "([a-zA-Z_]+)_rig_.*" "JingLei_dasd_rig_sds")
