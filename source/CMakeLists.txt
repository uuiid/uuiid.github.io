find_package(Boost  COMPONENTS
        locale
        iostreams
        program_options
        contract
        )

#仅头库
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Sqlpp11 CONFIG REQUIRED
        COMPONENTS
        sqlite3)

find_package(fmt CONFIG REQUIRED)
find_package(Simbody CONFIG REQUIRED)

set(UUIID_MANIFEST ${CMAKE_CURRENT_LIST_DIR}/uuid.manifest ${CMAKE_CURRENT_LIST_DIR}/win_exe.rc)
add_subdirectory(boost)
add_subdirectory(cpp)
add_subdirectory(sim_body)
