# ue4记录

## ue4 读写json

在ue4 读写json 中, 可以使用 FJsonObjectConverter::JsonObjectStringToUStruct 将 json 转换为 ustruct 类型,
- 第一个参数为 json 字符串
- 第二个是 要转换的 ustruct 指针
- 第三个 同下
- 第四个 都是 以CPF 开头的宏或者枚举值 **EPropertyFlags** 使用 FProperty::HasAnyPropertyFlags 
来检查这些值是否是必须还是跳过 **大部分情况直接给 CPF_None 或者 0 都行**

其中， 需要的 ustruct 中的属性值， 必须使用 **UPROPERTY()** 进行标记
