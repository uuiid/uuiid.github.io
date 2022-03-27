# c++17 自动注册的小技巧

在c++中, 由于没有完整的反射所以有时候会有一些不方便, 这时我们可以使用类模板结合静态变量
制作一个小型的反射系统, 并且结合 entt 来获得大部分反射可用
 
[演示](https://godbolt.org/z/P1ns6bxfE)

- 首先是一个需要注册的节点
```cpp
class node{
    std::int32_t p_{1};
};
```  
- 然后是一个全局列表
```cpp
std::multimap<std::int32_t, std::function<void()>>&  registered_functions(){
  static std::multimap<std::int32_t, std::function<void()>> instance{};
  return instance;
};
```
- 之后我们还需要一个模板类
```cpp
using reg_fun = void (*)();
/// Fun 注册的功能
/// priority_t 注册的优先级
template <reg_fun Fun, std::int32_t priority_t>
struct registrar_lambda {
  constexpr static const std::int32_t priority{priority_t};
 private:
  static registrar_lambda& register_() {
    static registrar_lambda l_t{};
    (void)registered;
    registered_functions().insert(
        std::make_pair(priority, [&]() { Fun(); }));
    return l_t;
  }
 public:
  static registrar_lambda& getInstance() {
    return register_();
  }
  inline static registrar_lambda& registered = getInstance();/// 内联静态变量, 普通静态变量没有尝试过, 不知道好不好用
  registrar_lambda() { (void)registered; /*特殊点, 防止编辑器优化使用, 不可消除*/ }
};
  
```
- 最后也就是使用方法了  
```cpp
namespace {
constexpr auto init_node = []() {
  /// 这里我们使用 entt 中的反射进行注册
  entt::meta<node>()
      .type();
};
class init_init_node_
    : public registrar_lambda<init_node, 2> {};
};

int main(int argc, char *argv[]){
    /// 这里是演示, 就不使用优先级进行分类运行了
    for(auto&& i: registered_functions()){
        i.second();
    }
}
```