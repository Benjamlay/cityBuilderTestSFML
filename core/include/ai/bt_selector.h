#ifndef BT_SELECTOR_H
#define BT_SELECTOR_H

#include "bt_composite.h"
#include "bt_node.h"

namespace core::ai {

  namespace behaviour_tree {

  class Selector : public Composite
  {
   public:

    void Reset() override;
    Status Tick() override;
  };

  }
}
#endif //BT_SELECTOR_H
