# cmake

## 调试cmake find_package
```cmake
    set(CMAKE_FIND_DEBUG_MODE TRUE)
    find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
    set(CMAKE_FIND_DEBUG_MODE FALSE)
```