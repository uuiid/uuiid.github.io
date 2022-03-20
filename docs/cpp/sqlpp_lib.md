# sqlpp

<details>
<summary>0001-fix-sqlite3.patch</summary>

```patch

diff --git a/CMakeLists.txt b/CMakeLists.txt
index a83ac43..74fc031 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -62,7 +62,7 @@ if(DEPENDENCY_CHECK AND BUILD_POSTGRESQL_CONNECTOR)
 endif()
 
 if(DEPENDENCY_CHECK AND BUILD_SQLITE3_CONNECTOR)
-  find_package(SQLite3 REQUIRED)
+  find_package(unofficial-sqlite3 REQUIRED)
 endif()
 
 if(DEPENDENCY_CHECK AND BUILD_SQLCIPHER_CONNECTOR)
@@ -89,7 +89,7 @@ target_compile_features(sqlpp11 INTERFACE cxx_std_11)
 
 
 if(BUILD_SQLITE3_CONNECTOR)
-  add_component(NAME sqlite3 DEPENDENCIES SQLite::SQLite3)
+  add_component(NAME sqlite3 DEPENDENCIES unofficial::sqlite3::sqlite3)
 endif()
 
 if(BUILD_SQLCIPHER_CONNECTOR)

```

</details>


<details>
<summary>0001-fix-sqlite3-config.patch</summary>

```patch

diff --git a/cmake/configs/Sqlpp11SQLite3Config.cmake b/cmake/configs/Sqlpp11SQLite3Config.cmake
index cf1098b..ee4c5dd 100644
--- a/cmake/configs/Sqlpp11SQLite3Config.cmake
+++ b/cmake/configs/Sqlpp11SQLite3Config.cmake
@@ -1,2 +1,2 @@
 include(CMakeFindDependencyMacro)
-find_dependency(SQLite3)
\ No newline at end of file
+find_dependency(unofficial-sqlite3)
\ No newline at end of file

```

</details>


<details>
<summary>0001-fix_ddl.patch</summary>

```patch

diff --git a/cmake/configs/Sqlpp11Config.cmake b/cmake/configs/Sqlpp11Config.cmake
index c50a71a..96d0c5b 100644
--- a/cmake/configs/Sqlpp11Config.cmake
+++ b/cmake/configs/Sqlpp11Config.cmake
@@ -51,7 +51,7 @@ endforeach()
 
 # Import "ddl2cpp" script
 if(NOT TARGET sqlpp11::ddl2cpp)
-  get_filename_component(sqlpp11_ddl2cpp_location "${CMAKE_CURRENT_LIST_DIR}/../../../bin/sqlpp11-ddl2cpp" REALPATH)
+  get_filename_component(sqlpp11_ddl2cpp_location "${CMAKE_CURRENT_LIST_DIR}/../../scripts/sqlpp11-ddl2cpp" REALPATH)
   if(NOT EXISTS "${sqlpp11_ddl2cpp_location}")
     message(FATAL_ERROR "The imported target sqlpp11::ddl2cpp references the file '${sqlpp11_ddl2cpp_location}' but this file does not exists.")
   endif()

```

</details>


<details>
<summary>portfile.cmake</summary>

```cmake

vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO rbock/sqlpp11
        REF 2bc89b34ad3cc37b6bca9a44a3529ff2d8fe211f # 0.60
        SHA512 6e2496959749422987aca21f333abb01648702b85e02acc711bbac398ca6a67d8be93a3d89fc1f8bad5446865725ff9bcc053e6229cb34627120b59469426266
        HEAD_REF master
        PATCHES
        0001-fix_ddl.patch
        0001-fix-sqlite3.patch
        0001-fix-sqlite3-config.patch
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
        FEATURES
        "mysql-connector" BUILD_MYSQL_CONNECTOR
        "sqlite3-connector" BUILD_SQLITE3_CONNECTOR
        )

# Use sqlpp11's own build process, skipping tests
vcpkg_configure_cmake(
        SOURCE_PATH ${SOURCE_PATH}
        PREFER_NINJA
        OPTIONS
        -DBUILD_TESTING:BOOL=OFF
        -DUSE_SYSTEM_DATE:BOOL=ON
        ${FEATURE_OPTIONS}
)

vcpkg_install_cmake()

# Move CMake config files to the right place
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/Sqlpp11 TARGET_PATH share/${PORT})

# Delete redundant and unnecessary directories
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug ${CURRENT_PACKAGES_DIR}/lib ${CURRENT_PACKAGES_DIR}/cmake ${CURRENT_PACKAGES_DIR}/include/date)

# Move python script from bin directory
file(COPY ${CURRENT_PACKAGES_DIR}/bin/sqlpp11-ddl2cpp DESTINATION ${CURRENT_PACKAGES_DIR}/scripts)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/bin/)

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)


```

</details>



<details>
<summary>vcpkg.json</summary>

```json

{
  "name": "sqlpp11",
  "version-string": "0.62",
  "port-version": 2,
  "description": "A type safe embedded domain specific language for SQL queries and results in C++.",
  "homepage": "https://github.com/rbock/sqlpp11",
  "dependencies": [
    "date"
  ],
  "default-features": [
    "core-library"
  ],
  "features": {
    "core-library": {
      "description": "By default only the core library will be installed."
    },
    "mysql-connector": {
      "description": "To also install connectors mysql",
      "dependencies": [
        "libmysql"
      ]
    },
    "sqlite3-connector": {
      "description": "To also install connectors sqlite3",
      "dependencies": [
        "sqlite3"
      ]
    }
  }
}


```

</details>