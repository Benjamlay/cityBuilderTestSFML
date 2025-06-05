#include "ai/bt_selector.h"
using namespace core::ai::behaviour_tree;

void Selector::AddChild(std::unique_ptr<Node> child)
{
  children_.push_back(std::move(child));
}

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
