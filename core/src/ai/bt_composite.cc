#include "ai/bt_composite.h"

using namespace core::ai::behaviour_tree;

void Composite::Reset() {
  childIdx = 0;
}

void Composite::AddChild(
    std::unique_ptr<Node> child) {
  children_.push_back(std::move(child));
}

