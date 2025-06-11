#include "ai/bt_selector.h"
using namespace core::ai::behaviour_tree;

void Selector::Reset()
{
    childIdx = 0;
}

Status Selector::Tick()
{
  while (childIdx < children_.size())
  {
    Status status = children_[childIdx]-> Tick();
     if (status == Status::kSuccess) {
       Reset();
       return Status::kSuccess;
     }
    if (status == Status::kRunning) {
      return Status::kRunning;
    }
    childIdx++;
  }

  return Status::kFailure;

}
