//
// Created by TD on 2022/4/16.
//
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

#include <iostream>
#include <boost/signals2.hpp>

// back-end
#include <boost/msm/back/state_machine.hpp>
// front-end
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
// for And_ operator
#include <boost/msm/front/euml/operator.hpp>
#include <utility>

/// 各种事件
/// 其中最好有一个异常事件
class my_err : public std::runtime_error {
 public:
  my_err() : std::runtime_error("my_err") {}
};

class play_run {
 public:
};
class rend_opt {
 public:
  std::int32_t int_p;
};

class quit_app {
 public:
};

class app : public boost::msm::front::state_machine_def<app> {
 public:
  struct empty : public boost::msm::front::state<> {
    template <typename Event, typename FSM>
    void on_entry(const Event &, FSM &) {
      std::cout << "开始空状态" << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const &, FSM &) {
      std::cout << "结束空状态" << std::endl;
    }
    struct internal_guard_fct {
      template <class EVT, class FSM, class SourceState, class TargetState>
      bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &) {
        std::cout << "Empty::internal_transition_table guard\n";
        return false;
      }
    };
    struct internal_action_fct {
      template <class EVT, class FSM, class SourceState, class TargetState>
      void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
        std::cout << "Empty::internal_transition_table action" << std::endl;
      }
    };
    struct internal_transition_table
        : boost::mpl::vector<
              //
              boost::msm::front::Internal<play_run, internal_action_fct, internal_guard_fct>
              //
              > {
    };
  };

  struct run_state : public boost::msm::front::state<> {
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &) {
      std::cout << "进入运行状态" << std::endl;
    }

    template <class Event, class FSM>
    void on_exit(Event const &, FSM &) {
      std::cout << "退出运行状态" << std::endl;
    }
    //    typedef boost::msm::back::args<void> accept_sig;
  };

  struct run_error_state : public boost::msm::front::state<> {
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &) {
      std::cout << "开始捕获异常: err" << std::endl;
    }

    template <class Event, class FSM>
    void on_exit(Event const &, FSM &) {
      std::cout << "处理完成异常: " << std::endl;
    }
  };

  struct init_state : public boost::msm::front::state<> {
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &) {
      std::cout << "初始化状态" << std::endl;
    }

    template <class Event, class FSM>
    void on_exit(Event const &, FSM &) {
      std::cout << "完成初始化" << std::endl;
    }
  };

  struct quit_state : public boost::msm::front::state<> {
    template <class Event, class FSM>
    void on_entry(Event const &, FSM &) {
      std::cout << "开始退出" << std::endl;
    }

    template <class Event, class FSM>
    void on_exit(Event const &, FSM &) {
      std::cout << "完成退出清理" << std::endl;
    }
  };

  // the initial state of the player SM. Must be defined
  typedef empty initial_state;

  // 各种动作
  struct TestFct {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "测试状态名称 " << typeid(EVT).name() << std::endl;
    }
  };

  struct start_playback {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::start_playback" << std::endl;
    }
  };

  struct init_app {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "开始初始化 app类, 使用默认命令行" << std::endl;
    }
  };

  struct quit_action {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "开始程序退出, 进行清理状态" << std::endl;
    }
  };

  struct read_opt {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &fsm, SourceState &, TargetState &) {
      std::cout << "开始使用传入的命令行读取配置" << std::endl;
      //      fsm.process_event(play());
    }
  };

  struct stop_playback {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::stop_playback" << std::endl;
    }
  };

  struct pause_playback {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::pause_playback" << std::endl;
    }
  };

  struct resume_playback {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::resume_playback" << std::endl;
    }
  };

  struct stop_and_open {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::stop_and_open" << std::endl;
    }
  };

  struct stopped_again {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      std::cout << "player::stopped_again" << std::endl;
    }
  };

  // guard conditions
  struct start_guard {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &evt, FSM &fsm, SourceState &src, TargetState &tgt) {
      if (typeid(TargetState) != typeid(play_run)) {
        std::cout << "没有进入开始状态, 可以开始" << std::endl;
        return true;
      }
      std::cout << "已经进入开始状态, 不需要开始" << std::endl;
      return false;
    }
  };

  struct good_disk_format {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &) {
      // to test a guard condition, let's say we understand only CDs, not DVD
      //      if (evt.disc_type != DISK_CD) {
      //        std::cout << "wrong disk, sorry" << std::endl;
      //        return false;
      //      }
      return true;
    }
  };

  struct always_true {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &) {
      return true;
    }
  };

  struct internal_guard {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &evt, FSM &, SourceState &, TargetState &) {
      std::cout << "Empty::internal guard\n";
      return false;
    }
  };

  // Transition table for player
  using none = boost::msm::front::none;
  //  using namespace boost::msm::front;
  //  using namespace boost::msm::front::euml;
  template <typename... Arg>
  using Row = boost::msm::front::Row<Arg...>;
  template <typename... Arg>
  using And_ = boost::msm::front::euml::And_<Arg...>;
  template <typename... Arg>
  using ActionSequence_ = boost::msm::front::ActionSequence_<Arg...>;
  // clang-format off
  struct transition_table
      : boost::mpl::vector<
            //    Start     Event         Next      Action                     Guard
            //  +---------+-------------+---------+---------------------------+----------------------+
            Row<empty,     play_run,    run_state, init_app,                   boost::msm::front::none>,
            Row<empty,     rend_opt,    init_state,read_opt,                   And_<good_disk_format, always_true> >,
            // internal transition inside the stt: none as Target
            Row<empty,     quit_app,    quit_state,quit_action,                boost::msm::front::none>,
            //  +---------+-------------+---------+---------------------------+----------------------+
            Row<run_state, play_run,    run_state, ActionSequence_<
                                                    boost::mpl::vector<TestFct,
                                                                start_playback>
                                                    >,                         start_guard>,
//            Row<run_state, rend_opt,    init_state,none,                       boost::msm::front::none>,
            Row<run_state, quit_app,    quit_state, quit_action,               none>,
            //  +---------+-------------+---------+---------------------------+----------------------+
            Row<init_state,  play_run,  run_state,  init_app,                  none>,
            Row<init_state,  quit_app,  quit_state, quit_action,               none>
            //  +---------+-------------+---------+---------------------------+----------------------+
            > {
    // clang-format on
  };

  // Replaces the default no-transition response.
  template <class FSM, class Event>
  [[maybe_unused]] void no_transition(const Event &e, FSM &, int state) {
    std::cout << "no transition from state " << state
              << " on event " << typeid(e).name() << std::endl;
  }
};

using app_msm = boost::msm::back::state_machine<app>;

int main(int argc, char *argv[]) {
  app_msm l_app{};
  l_app.start();
  std::cout << " -> " << *l_app.current_state() << std::endl;
  l_app.process_event(rend_opt{});
  std::cout << " -> " << *l_app.current_state() << std::endl;
  l_app.process_event(play_run{});
  std::cout << " -> " << *l_app.current_state() << std::endl;
  l_app.process_event(quit_app{});
  std::cout << " -> " << *l_app.current_state() << std::endl;
  l_app.get_state<app_msm::run_state &>();
  l_app.stop();
}
