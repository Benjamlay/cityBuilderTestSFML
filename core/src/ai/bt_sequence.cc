#include "ai/bt_sequence.h"

using namespace core::ai::behaviour_tree;

Status Sequence::Tick() {
  while (childIdx < children_.size())
  {
    Status status = children_[childIdx]-> Tick();
    if (status == Status::kFailure) {
      Reset();
      return Status::kFailure;
    }
    if (status == Status::kRunning) {
      return Status::kRunning;
    }
    childIdx++;
  }

  return Status::kSuccess;
}



