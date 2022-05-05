//
// Created by TD on 2022/4/29.
//
#pragma once

#include <map>
#include <string>
#include <functional>
#include <optional>

#include <server/exception/json_rpc_error.h>
#include <server/rpc_reply.h>

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/erase.hpp>

namespace detail {
template <class ParamSequence, std::size_t... Indices>
auto unpack_params(ParamSequence, std::index_sequence<Indices...>) -> std::tuple<boost::mpl::at_c<ParamSequence, Indices>...>;
}

class rpc_server {
 public:
  using call_fun = std::function<rpc_reply(const std::optional<nlohmann::json>&)>;

 private:
  std::map<std::string,
           call_fun>
      fun_list_{};

 public:
  rpc_server();
  void register_fun(const std::string& in_name, const call_fun& in_call);

  /**
   * 模板注册方法
   * @tparam Fun_T 传入的函数模板
   * @param in_name rpc名称
   * @param in_fun_t 传入的函数
   */
  template <typename Fun_T>
  void register_fun_t(const std::string& in_name, Fun_T&& in_fun_t) {
    register_fun(in_name, [&](const std::optional<nlohmann::json>& in_arg) -> rpc_reply {
      /// @brief 分解注册函数中的类型
      using Fun_Result                  = typename boost::function_types::result_type<decltype(&Fun_T::operator())>::type;
      //      using Fun_Result = typename decltype(std::function<typename Fun_T>{})::result_type;
      using Fun_Parameter_All           = typename boost::function_types::parameter_types<decltype(&Fun_T::operator())>::type;
      using Fun_Parameter               = typename boost::mpl::erase<Fun_Parameter_All, boost::mpl::begin<Fun_Parameter_All>>;
      constexpr auto Fun_Parameter_Size = boost::function_types::function_arity<decltype(&Fun_T::operator())>::value - 1;

      //      typedef typename boost::function_types::result_type<Fun_T>::type Fun_Result;
      rpc_reply rpc_reply_{};
      try {
        nlohmann::json json_l{};
        /// @brief 使用编译期测试函数参数, 节约调用时间
        if constexpr (Fun_Parameter_Size == 0) {
          /// @brief 测试函数返回值, 返回为 void 时, 不进行序列化
          if constexpr (std::is_same_v<Fun_Result, void>) {
            in_fun_t();
          } else {
            json_l = in_fun_t();
          }

        } else {
          /// @brief 将boost mpl vector 转换为元组后调用
          using Fun_Parameter_tuple =
              decltype(detail::unpack_params(
                  std::declval<Fun_Parameter>(),
                  std::make_index_sequence<Fun_Parameter_Size>()));
          if constexpr (std::is_same_v<Fun_Result, void>) {
            std::apply(in_fun_t, *in_arg->template get<Fun_Parameter_tuple>());
          } else {
            json_l = std::apply(in_fun_t, *in_arg->template get<Fun_Parameter_tuple>());
          }
        }
        rpc_reply_.result = json_l;
      } catch (const rpc_error_exception& err) {
        rpc_reply_.result = rpc_error{err};
      }
      return rpc_reply_;
    });
  };

  rpc_reply operator()(const std::string& in_name,
                       const std::optional<nlohmann::json>& in_parm) const;
};
class session;
class rpc_server_ref {
 public:
  using call_fun = std::function<rpc_reply(const std::optional<nlohmann::json>&)>;

 private:
  std::map<std::string,
           call_fun>
      fun_list_{};

  std::weak_ptr<rpc_server> server;

 public:
  explicit rpc_server_ref(std::weak_ptr<rpc_server> in_server,
                          const std::function<void()>& in_close_fun);
  rpc_reply operator()(const std::string& in_name,
                       const std::optional<nlohmann::json>& in_parm) const;
};
