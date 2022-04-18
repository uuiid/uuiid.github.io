add_executable(uuiid_std_regex
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )
target_link_libraries(uuiid_std_regex PUBLIC fmt::fmt Boost::locale)
add_test(NAME uuiid_std_regex_com COMMAND uuiid_std_regex "([a-zA-Z_]+)_rig_.*" "JingLei_dasd_rig_sds")
add_test(NAME uuiid_std_regex_com2 COMMAND uuiid_std_regex [[([^\x00-\xff]+[:|：][^\x00-\xff]+)$]] "薛南明：护住小姐！")
add_test(NAME uuiid_std_regex_com3 COMMAND uuiid_std_regex [[([^\x00-\xff]+[:|：][^\x00-\xff]+)$]] "薛南明护住小姐！")
