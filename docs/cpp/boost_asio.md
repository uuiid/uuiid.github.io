# boost asio 示例 (asio json rpc 例子)

## 服务端

服务端需要 **io_context** 和一个地址作为构造函数, 构造一个 **acceptor** 在
这里我们使用 **tcp** 连接作为基本的连接类型, 其中服务端异步等待会话连接, 并生成会话

### 服务端基本会话

这里需要启用 **std::enable_shared_from_this** 功能, 保持会话的生命周期



