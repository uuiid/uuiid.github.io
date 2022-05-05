# boost asio 示例 (asio json rpc 例子)

## 服务端

服务端需要 **io_context** 和一个地址作为构造函数, 构造一个 **acceptor** 在
这里我们使用 **tcp** 连接作为基本的连接类型, 其中服务端异步等待会话连接, 并生成会话

### 服务端基本会话

这里需要启用 **std::enable_shared_from_this** 功能, 保持会话的生命周期

### 注册功能分解

在使用rpc 服务中, 最重要的时注册功能的分解和转换, 我们使用 boost
**callable_traits** 中的 return_type_t args_t 模板函数分解传入的 Fun

### 异常和返回值

在注册中, 使用异常, 并将异常与rpc返回值进行转换, 而不是进行返回值进行错误检查


