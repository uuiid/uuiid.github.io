# c++ 的一些笔记
 

## 使用vcpkg 的一些技巧


### opencv 库

在vcpkg中, opencv 库可是说是一个必不可少的库, 其中最令人无奈的时opencv freetype组件没有办法编译, 需要添加中午水印就很令人难受,
需要改造一下vcpkg中的`0016-fix-freetype-contrib.patch`补丁文件, 改为一下内容

<details>
<summary>0016-fix-freetype-contrib.patch 内容</summary>

```patch
diff --git a/modules/freetype/CMakeLists.txt b/modules/freetype/CMakeLists.txt
index 6dd4aaf..e734e97 100644
--- a/modules/freetype/CMakeLists.txt
+++ b/modules/freetype/CMakeLists.txt
@@ -3,8 +3,12 @@ if(APPLE_FRAMEWORK)
   ocv_module_disable(freetype)
 endif()
 
-ocv_check_modules(FREETYPE freetype2)
-ocv_check_modules(HARFBUZZ harfbuzz)
+if(WITH_FREETYPE)
+find_package(freetype CONFIG REQUIRED)
+find_package(harfbuzz CONFIG REQUIRED)
+set(FREETYPE_FOUND TRUE)
+set(HARFBUZZ_FOUND TRUE)
+endif()

 if(OPENCV_INITIAL_PASS)
   if(NOT FREETYPE_FOUND)


```

</details>  

### sqlpp11 库

sqlpp库在vcpkg中已经过时了太多了, 需要重新更改 [sqlpp更改内容](/cpp/sqlpp_lib.md)
