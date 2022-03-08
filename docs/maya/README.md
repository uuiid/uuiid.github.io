# maya工具

## c++ 的环境配置
在c++制作maya插件时, 在maya 2018 以前都是使用 vs 项目向导, 在2018 以后都是使用cmake 配置  
在本书中,**一律使用camke 进行配置**, 在maya2019官方的帮助文档中有了一些配置camke的帮助文件, 
但是由于要使用多个maya版本进行插件编译时,会出现需要切换多次cmake项目的问题, 所以,我们使用maya的版本号来区别 cmake 寻找到的 maya包

[FindMaya](maya/FindMaya.md)

使用方法
``` cmkae
foreach (MAYA_VERSION IN ITEMS 2018 2019 2020)
        find_package(Maya ${MAYA_VERSION} REQUIRED)
        add_library(test_${MAYA_VERSION})
        target_link_libraries(test_${MAYA_VERSION} PRIVATE maya::maya_${MAYA_VERSION}_all)
endforeach ()

```

## maya中的MObject

在maya中， MObject 是一个基础的不能在基础的类的， 基本上所有的maya操作都要使用这个东西
MObject 可以类比为一个 c++ 标准中的 std::any 类, 在maya 的头文件的的定义也可以看出,
他是一个指针加一个枚举值的属性, 就像一个 void指针和一个 std::type_index 一样
基本上所有的操作都是先要测试 MObject 的 Mfn 类型  

## maya中的 mfn

maya中的mfn和mobj一样的重要, 他代表的这个obj可以附加到什么函数集上

