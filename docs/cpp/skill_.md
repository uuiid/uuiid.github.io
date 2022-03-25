# 一些小技巧

## 一次性读入整个文件
<details>
<summary>一次性读入整个文件</summary>

```cpp
std::ifstream l_ifstream{in_path};
std::string l_auth{std::istreambuf_iterator(l_ifstream), std::istreambuf_iterator<char>()};
```

</details>

## 单例 
<details>
<summary>单例</summary>

```cpp

class single{
  public:

};

```

</details>