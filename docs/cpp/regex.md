# 正则表达式

在std 库中 正则表达式也是一个很有用的部件

## 注意事项

- 在正则表达式中, 是默认使用 **ECMAScript** 作为正则表达式的引擎的, 在使用时,
  需要稍微注意一下和其他引擎的区别
- 在正则表达式中, 如果想要测试中文, 那么需要使用 **std::wstring** 字符, 和
  **std::wregex** 正则表达式
- 中文需要匹配的话 `[\u4e00-\u9fa5]` 这个中表示utf字符中从**0x4e00**到**0x9fa5**的字符(16进制)
  这个是前几年的结果了, 现在好像结束不是在**0x9fa5**
- 中文中的标点和英文标点有不同, 有时候需要特殊处理

