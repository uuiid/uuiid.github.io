add_executable(uuiid_sim_body
        main.cpp
        ../../win_exe.rc
        ../../uuiid.manifest
        )
target_link_libraries(uuiid_sim_body PUBLIC fmt::fmt Boost::locale
        SimTKcommon
        SimTKmath
        SimTKsimbody)
target_compile_definitions(uuiid_sim_body PRIVATE _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_test(NAME uuiid_sim_body_com COMMAND uuiid_std_fmt " ")
