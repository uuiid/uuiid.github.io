# ue4记录

## ue4 GENERATED_UCLASS_BODY() 和 GENERATED_BODY()

GENERATED_UCLASS_BODY() 展开时会声明一个构造函数, 
GENERATED_BODY() 需要自己声明构造函数

## ue4 自定义资产拖拽到世界关卡

需要创建一个 UActorFactory 的工厂子类, 如果需要

## 获取一个临时包
使用 GetTransientPackage() 获取一个临时包, 可用将不需要保存的对象放入其中

## 自动化导入
USequencerToolsFunctionLibrary(SequencerTools.h) 这个类是大多数时候的使用, 如果还要细粒度的控制, 可以使用 MovieSceneToolHelpers 这个类


## ue4 路径表示
- 参考/文本路径 `StaticMesh'/Game/MyFolder/MyAsset.MyAsset'`
- 全名 `StaticMesh /Game/MyFolder/MyAsset.MyAsset`
- 路径名(也可已是对象名称) `/Game/MyFolder/MyAsset.MyAsset`
- 包名称 `/Game/MyFolder/MyAsset`
- 路径名称 `/Game/MyNewFolder/` 或者 `/Game/MyNewFolder`
- 蓝图类路径名 (据我观察并没有找到代码) `/Game/MyFolder/myclass.myclass_C`
- 蓝图名称 **myclass_C** (myclass 是包名称)
- 基本上**路径名称**和**对象名称**相同

## ue4 读写文件 
使用  FFileHelper::SaveStringToFile 写入文件
使用  FFileHelper::LoadFileToString 写入文件

## ue4 读写json

在ue4 读写json 中, 可以使用 FJsonObjectConverter::JsonObjectStringToUStruct 将 json 转换为 ustruct 类型,
- 第一个参数为 json 字符串
- 第二个是 要转换的 ustruct 指针
- 第三个 同下
- 第四个 都是 以CPF 开头的宏或者枚举值 **EPropertyFlags** 使用 FProperty::HasAnyPropertyFlags 
来检查这些值是否是必须还是跳过 **大部分情况直接给 CPF_None 或者 0 都行**

其中， 需要的 ustruct 中的属性值， 必须使用 **UPROPERTY()** 进行标记
在使用属性标记后，TArray 数组将对应 json 中数组， 每个 struct 将对应一个json obj 对象，

<details>
<summary>c++ 示例 </summary>

```c++
#define UENUM(...)
#define GENERATED_BODY(...)
#define UPROPERTY(...)
#define USTRUCT(...)



#define UENUM(...)
#define GENERATED_BODY(...)
#define UPROPERTY(...)
#define USTRUCT(...)


UENUM()
enum class EEnumType : uint8 { None = 0, Abc, Fbx };

USTRUCT()
struct FTest {
  GENERATED_BODY()

  UPROPERTY()
  FString string;

  UPROPERTY()
  uint64 num;

  UPROPERTY()
  EEnumType p_enum;

};

USTRUCT()
struct FGroup {
  GENERATED_BODY()

  UPROPERTY()
  TArray<FTest> groups;
};

FString to_json(){
    FTest l_tets1{};
    FTest l_tets2{};
    FGroup l_group{};
    l_group.groups.Add(l_tets1);
    l_group.groups.Add(l_tets2);

    FString l_str{};
    FJsonObjectConverter::UStructToJsonObjectString<FGroup>(
      l_group, l_str, CPF_None, CPF_None);
    return FString
}
```

</details>

<details>
<summary>序列化后</summary>

```json
{
	"groups": [
		{
			"string": "str",
			"p_enum": "Abc",
			"num": 1001
		},
		{
			"string": "str",
			"p_enum": "Abc",
			"num": 1001
		}
	]
}
```

</details>


## ue4 反射

在ue4 中, 有一部分继承 uobject 的类是没有导出的, 在使用插件动态库时, 如果需要使用的话, 就需要使用
ue4 中的反射模块,其中, 最主要的时 **UClass** 这个类, 在使用时, 我们需要找到所有的 uclass 实例, 
使用模板迭代器 TObjectIterator<T> 进行迭代, 然后寻找所需要的类， 之后直接获取默认值

<details>
<summary>c++ 示例</summary>

```c++
  for (TObjectIterator<UClass> it{}; it; ++it) {
    if (it->IsChildOf(UFactory::StaticClass())) {
      if (it->GetName() == "LevelSequenceFactoryNew") {
        it->GetDefaultObject<UFactory>();
      }
    }
  }

```

</details>
 
## UE4命令行

### 编译工程

最好使用 `Developer Command Prompt for VS 2019` 打开vscode, 这样智能感知工作会好用很多

使用 GenerateProjectFiles.bat 生成项目文件 `GenerateProjectFiles.bat -projectfiles -project="path to project" -game -engine -vscode`, 
也可以修改 Engine\Saved\UnrealBuildTool\BuildConfiguration.xml 文件中的选项进行更改, 将 `-vscode` 替换为 `-2019`即可生成 **Microsoft Visual Studio 2019** 项目,
<details>
<summary>文件内容</summary>

```xml
<?xml version="1.0" encoding="utf-8"?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
    <ProjectFileGenerator>
        <Format>VisualStudioCode</Format>
    </ProjectFileGenerator>
</Configuration>

```

</details>
 
 但是对于 生成的vscode 项目在工作中, 经常会出现一些瑕疵, 可以将 json 中的 ` C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\bin\\HostX64\\x64\\ ` 更改为空, 然后使用 `Developer Command Prompt for VS 2019` 打开vscode 这样可以正常使用, 而且 智能感知也可以正常工作


当然也可以直接传入到 UnrealBuildTool.exe 中, 其实 GenerateProjectFiles.bat 也是调用的 UnrealBuildTool.exe  只是在前期会做一大串的检查工作, 当第一次使用git clone ue4 项目时,
就没有办法直接使用 UnrealBuildTool.exe 了, 因为没有生成 UnrealBuildTool.exe 只能使用 `GenerateProjectFiles.bat`

### 编译材质
 -run=DerivedDataCache


```batch

```

### ue4editor-cmd.exe命令行

 - skipcompile 跳过编译