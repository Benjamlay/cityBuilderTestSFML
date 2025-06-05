#ifndef ACTION_H
#define ACTION_H
#include <functional>

#include "bt_node.h"

namespace core::ai {
    namespace behaviour_tree {

    class Action : public Node {

      std::function<Status()> action_;
     public:
        explicit Action(std::function<Status()> action) : action_(action){}
        void Reset() override {};
        Status Tick() override {
          return action_();
        }
    };
    }
}
#endif //ACTION_H
