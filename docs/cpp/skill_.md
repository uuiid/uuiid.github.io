# 一些小技巧

## 一次性读入整个文件

```cpp
std::ifstream l_ifstream{in_path};
std::string l_auth{std::istreambuf_iterator(l_ifstream), std::istreambuf_iterator<char>()};
```
 
## 单例

[演示]](https://godbolt.org/z/8qrzM8vYd)

<details>
<summary>单例</summary>

```cpp

class single{
  single();

  public:

  ~single();
  
  single(single& in) = delete;/// 复制构造删除
  single& operator=(single& in) = delete; /// 复制赋值删除
  single(single&& in) = delete;/// 移动构造删除
  single& operator=(single&& in) = delete; /// 复制构造删除

  static single& get();/// 单例获取

};
single::single()= default;
/// 重点来了, 在这个使用静态局部变量获取单例的实例
single& single::get(){
  static single instance{};
  return instance;
}

```

</details>


