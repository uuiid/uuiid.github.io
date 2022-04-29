//
// Created by TD on 2022/4/29.
//
#pragma once
#include <vector>
#include <set>
#include <memory>

class session;
class session_manager {
 private:
  std::set<std::shared_ptr<session>> session_list_;

 public:
  session_manager();

  template <typename Session, typename... Args>
  void start(const std::shared_ptr<Session>& in_session, Args... args) {
    session_list_.template emplace(in_session);
    in_session->start(std::forward<Args>(args)...);
  };
  void stop(const std::shared_ptr<session>& in_session);
  void stop_all();
};
