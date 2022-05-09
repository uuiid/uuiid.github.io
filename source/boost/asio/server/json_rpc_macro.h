//
// Created by TD on 2022/5/9.
//

#pragma once

#include <boost/preprocessor.hpp>
#define DOODLE_RPC_GET_FUN_NAME_STR(list) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, list))
#define DOODLE_RPC_GET_FUN_NAME(list) BOOST_PP_TUPLE_ELEM(1, list)
#define DOODLE_RPC_GET_FUN_RETURN(list) BOOST_PP_TUPLE_ELEM(0, list)
#define DOODLE_RPC_TO_ARG_DEF(elem) BOOST_PP_TUPLE_ELEM(2, elem) arg
#define DOODLE_RPC_TO_ARG(list) BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(list), 3), DOODLE_RPC_TO_ARG_DEF(list), BOOST_PP_EMPTY())
#define DOODLE_RPC_TO_ARG2(list) BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(list), 3), arg, BOOST_PP_EMPTY())
#define DOODLE_RPC_FUN_DECLARATION(r, data, elem) \
  virtual DOODLE_RPC_GET_FUN_RETURN(elem) DOODLE_RPC_GET_FUN_NAME(elem)(DOODLE_RPC_TO_ARG(elem)) = 0;

#define DOODLE_RPC_CALL_FUN(r, data, elem)                                               \
  register_fun_t(DOODLE_RPC_GET_FUN_NAME_STR(elem),                                      \
                 [this](DOODLE_RPC_TO_ARG(elem)) -> DOODLE_RPC_GET_FUN_RETURN(elem) {    \
                   return this->DOODLE_RPC_GET_FUN_NAME(elem)(DOODLE_RPC_TO_ARG2(elem)); \
                 });

#define DOODLE_RPC_DECLARATION(rpc_server_name, ...)                                            \
  class rpc_server_name : public rpc_server {                                                   \
   public:                                                                                      \
    using rpc_server::rpc_server;                                                               \
    void init_register() override {                                                             \
      BOOST_PP_SEQ_FOR_EACH(DOODLE_RPC_CALL_FUN, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__));     \
    }                                                                                           \
    BOOST_PP_SEQ_FOR_EACH(DOODLE_RPC_FUN_DECLARATION, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
  };
