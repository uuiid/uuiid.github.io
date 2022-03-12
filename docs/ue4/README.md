# ue4记录

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

```batch
"%EngineDir%/Engine/Binaries/DotNET/UnrealBuildTool.exe"  -projectfiles -project="%GameDir%\MyGame.uproject" -game -engine -VSCode   //windows下生成vscode项目工程

"%EngineDir%/Engine/Binaries/DotNET/UnrealBuildTool.exe"  -projectfiles -project="%GameDir%\MyGame.uproject" -game -engine -2019  //windows下生成vs2019项目工程  注：vs2019使用的c++14

```
### ue4editor.exe命令行

 - skipcompile 跳过编译着色器