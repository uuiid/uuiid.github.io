find_package(Boost  COMPONENTS
        locale
        iostreams
        program_options
        contract
        )
set(UUIID_MANIFEST ${CMAKE_CURRENT_LIST_DIR}/uuid.manifest ${CMAKE_CURRENT_LIST_DIR}/win_exe.rc)
add_subdirectory(boost)
