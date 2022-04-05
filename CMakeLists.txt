cmake_minimum_required(VERSION 3.23)
#添加模块文件
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(GetGitVersion)

get_git_version(
        WORK_DIR ${CMAKE_SOURCE_DIR}
)

project(uuiid
        VERSION "${v_short}"
        DESCRIPTION "一些小例子"
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/uuiid)
# 添加一些全局必要的宏
add_compile_definitions(QT_NO_KEYWORDS UNICODE _UNICODE NOMINMAX)
# 全局警告
#add_compile_options(/W4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#使用中文
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

enable_testing()
add_subdirectory(source)
