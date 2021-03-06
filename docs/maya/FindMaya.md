# 寻找maya的cmake 文件

``` cmake
# Distributed under the GNU 3.0 License.  See accompanying

#[=======================================================================[.rst:
FindMaya
-------

Finds the Maya library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``maya::maya_${Maya_VERSION}_all``
  The Maya library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:


``Maya_INCLUDE_DIRS``
  Include directories needed to use Maya.
``Maya_LIBRARIES``
  Libraries needed to link to Maya.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``MAYA_INCLUDE_DIR_${Maya_FIND_VERSION}``
  The directory containing ``Maya.h``.
`` maya_${Maya_FIND_VERSION}_all ``
  The path to the Maya library.

#]=======================================================================]

include(CMakePrintHelpers)

if (WIN32)
    # 现在的使用默认的maya安装路径寻找， 由于工作是在 win 平台上的， 并没有兼容其他的平台
    set(MAYA_DEFAULT_LOCATION "C:/Program Files/Autodesk/Maya${Maya_FIND_VERSION}")
    set(OPEN_MAYA OpenMaya)
endif ()

# 寻找maya 中的基本路径 使用 ${Maya_FIND_VERSION} 添加版本
find_path(MAYA_BASE_DIR_${Maya_FIND_VERSION}
        include/maya/MFn.h
        HINTS
        ${MAYA_DEFAULT_LOCATION}
        DOC
        "maya 基本路径"
        )

# 寻找maya 中的基本导入路径 使用 ${Maya_FIND_VERSION} 添加版本
find_path(MAYA_INCLUDE_DIR_${Maya_FIND_VERSION}
        maya/MFn.h
        HINTS
        ${MAYA_DEFAULT_LOCATION}
        PATH_SUFFIXES
        "include/"
        REQUIRED
        DOC
        "maya 导入路径"
        )

# 寻找maya 中的库路径 使用 ${Maya_FIND_VERSION} 添加版本
find_path(MAYA_LIBRARY_DIR_${Maya_FIND_VERSION}
        ${OPEN_MAYA}.lib
        HINTS
        ${MAYA_DEFAULT_LOCATION}
        PATH_SUFFIXES
        "lib"
        REQUIRED
        DOC
        "maya 连接库"
        )

# 寻找maya 中的动态库路径 使用 ${Maya_FIND_VERSION} 添加版本
find_path(MAYA_DLL_LIBRARY_DIR_${Maya_FIND_VERSION}
        ${OPEN_MAYA}.dll
        HINTS
        ${MAYA_DEFAULT_LOCATION}
        PATH_SUFFIXES
        "bin"
        REQUIRED
        DOC
        "maya dll 位置"
        )
#创建maya库列表
set(MAYA_LIBS_TO_FIND
        OpenMaya
        OpenMayaAnim
        OpenMayaFX
        OpenMayaRender
        OpenMayaUI
        Image
        Foundation
        MetaData # 元数据连接库
        # IMFbase
        cg
        cgGL
        clew
        )
# 添加maya 接口库
add_library(maya_${Maya_FIND_VERSION}_all INTERFACE IMPORTED)
# 循环查找maya 库列表
foreach (MAYA_LIB ${MAYA_LIBS_TO_FIND})
    find_library(MAYA_${MAYA_LIB}_LIBRARY_${Maya_FIND_VERSION}
            ${MAYA_LIB}
            HINTS
            ${MAYA_LIBRARY_DIR_${Maya_FIND_VERSION}}
            REQUIRED
            DOC
            "寻找maya ${MAYA_LIB}库"
            NO_CMAKE_SYSTEM_PATH
            )
    find_file(
            MAYA_${MAYA_LIB}_LIBRARY_dll_${Maya_FIND_VERSION}
            ${MAYA_LIB}.dll
            HINTS
            ${MAYA_DLL_LIBRARY_DIR_${Maya_FIND_VERSION}}
            REQUIRED
            DOC
            "寻找maya ${MAYA_LIB} dll库"
            NO_CMAKE_SYSTEM_PATH
    )

    if (MAYA_${MAYA_LIB}_LIBRARY_${Maya_FIND_VERSION})
        list(APPEND MAYA_LIBRARY ${MAYA_${MAYA_LIB}_LIBRARY_${Maya_FIND_VERSION}})
        # 添加基础库
        add_library(maya_${Maya_FIND_VERSION}_${MAYA_LIB} SHARED IMPORTED)
        # 添加基础库的别名
        add_library(maya::maya_${Maya_FIND_VERSION}_${MAYA_LIB} ALIAS maya_${Maya_FIND_VERSION}_${MAYA_LIB})
        # 设置属性
        set_property(TARGET maya_${Maya_FIND_VERSION}_${MAYA_LIB} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE)
        set_property(TARGET maya_${Maya_FIND_VERSION}_${MAYA_LIB} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG)
        target_include_directories(maya_${Maya_FIND_VERSION}_${MAYA_LIB} INTERFACE ${MAYA_INCLUDE_DIR_${Maya_FIND_VERSION}})

        set_target_properties(maya_${Maya_FIND_VERSION}_${MAYA_LIB} PROPERTIES
                IMPORTED_LOCATION "${MAYA_${MAYA_LIB}_LIBRARY_dll_${Maya_FIND_VERSION}}"
                IMPORTED_IMPLIB "${MAYA_${MAYA_LIB}_LIBRARY_${Maya_FIND_VERSION}}"
                )
        target_link_libraries(maya_${Maya_FIND_VERSION}_all INTERFACE maya_${Maya_FIND_VERSION}_${MAYA_LIB})
    endif ()
endforeach ()

#foreach(MAYA_QT5_LIB ${MAYA_LIBS_TO_QT_FIND})
#  find_library(MAYA_QT_${MAYA_QT5_LIB}_LIBRARY
#  ${MAYA_QT5_LIB}
#  HINTS
#   ${MAYA_LIBRARY_DIR}
#  REQUIRED
#  DOC
#   "寻找maya qt ${MAYA_QT5_LIB} 组件"
#  NO_CMAKE_PATH
#  NO_CMAKE_ENVIRONMENT_PATH
#  NO_CMAKE_SYSTEM_PATH
#  NO_DEFAULT_PATH
#  )
#  if(MAYA_QT_${MAYA_QT5_LIB}_LIBRARY)
#    list(APPEND MAYA_QT5_LIBRARY ${MAYA_QT_${MAYA_QT5_LIB}_LIBRARY})
#  endif()
#endforeach()


include(FindPackageHandleStandardArgs)


find_package_handle_standard_args(Maya
        REQUIRED_VARS MAYA_INCLUDE_DIR_${Maya_FIND_VERSION}
        REASON_FAILURE_MESSAGE "maya 库中的组件没有找到"
        )
# 这些宏选项都在 maya devkit.cmake 文件中有, 需要复制过来
target_compile_definitions(
        maya_${Maya_FIND_VERSION}_all
        INTERFACE
        -DNT_PLUGIN # maya dev开发包中指定的不同平台的插件标志(win)
        -D_WIN32
        -DOSWin_
        -DUSERDLL
        -DCRT_SECURE_NO_DEPRECATE
        -D_HAS_ITERATOR_DEBUGGING=0
        -D_CRT_SECURE_NO_WARNINGS
        -DPARTIO_WIN32
)

add_library(maya::maya_${Maya_FIND_VERSION}_all ALIAS maya_${Maya_FIND_VERSION}_all)

```