# boost 状态机

## boost 状态机首选前端

在boost(1.78)文档中, 指示首选前端为**函子前端**, 我们也就听从boost库的建议, 在这里制作函子前端

### 行

在boost状态机中, **行**可用说是一个状态到另一个状态的表示 包含了一下四项

- 开始状态
- 事件
- 目标(结束状态)
- 动作 这个可以是**空**
- 守卫 这个可以是**空**

函子的函数签名是 ↓, 同时,守卫的返回值不同, 守卫的返回值为 bool

```cpp
//            状态机       事件           源状态         目标状态
template <class Fsm, class Evt, class SourceState, class TargetState>
void operator()(Evt const&, Fsm& fsm, SourceState&, TargetState& ){

} 
```


