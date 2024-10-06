#include "Set.h"

// BSTNode.cpp

#include "Set.h"

std::shared_ptr<BSTNode> BSTNode::subtree_find(int k) {
  if (k == item) {
    return std::static_pointer_cast<BSTNode>(shared_from_this());
  }
  if (k < item && left) {
    return std::static_pointer_cast<BSTNode>(left)->subtree_find(k);
  }
  if (k > item && right) {
    return std::static_pointer_cast<BSTNode>(right)->subtree_find(k);
  }
  return nullptr;
}
