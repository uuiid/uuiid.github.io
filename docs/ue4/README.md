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

``` c++
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

序列化后

``` json
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