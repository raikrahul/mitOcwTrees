// BinaryNode.cpp

#include "BinaryNode.h"
#include <algorithm>
#include <vector>

int BinaryNode::height() {
  int leftHeight = (left ? left->height() : -1);
  int rightHeight = (right ? right->height() : -1);
  return 1 + std::max(leftHeight, rightHeight);
}

void BinaryNode::print(std::ostream &out) {
  if (left) {
    left->print(out);
  }
  out << item << " ";
  if (right) {
    right->print(out);
  }
}

std::vector<std::shared_ptr<BinaryNode>> BinaryNode::subtree_iter() {
  std::vector<std::shared_ptr<BinaryNode>> nodes;
  subtree_iter_helper(nodes);
  return nodes;
}

void BinaryNode::subtree_iter_helper(
    std::vector<std::shared_ptr<BinaryNode>> &nodes) {
  if (left) {
    left->subtree_iter_helper(nodes);
  }
  nodes.push_back(shared_from_this());
  if (right) {
    right->subtree_iter_helper(nodes);
  }
}

std::shared_ptr<BinaryNode> BinaryNode::subtree_first() {
  if (left) {
    return left->subtree_first();
  } else {
    return shared_from_this();
  }
}

std::shared_ptr<BinaryNode> BinaryNode::subtree_last() {
  if (right) {
    return right->subtree_last();
  } else {
    return shared_from_this();
  }
}

std::shared_ptr<BinaryNode> BinaryNode::successor() {
  if (right) {
    return right->subtree_first();
  }
  std::shared_ptr<BinaryNode> A = shared_from_this();
  while (A->parent.lock() && A == A->parent.lock()->right) {
    A = A->parent.lock();
  }
  return A->parent.lock();
}

std::shared_ptr<BinaryNode> BinaryNode::predecessor() {
  if (left) {
    return left->subtree_last();
  }
  std::shared_ptr<BinaryNode> A = shared_from_this();
  while (A->parent.lock() && A == A->parent.lock()->left) {
    A = A->parent.lock();
  }
  return A->parent.lock();
}

void BinaryNode::subtree_insert_before(std::shared_ptr<BinaryNode> B) {
  // If the current node has a left child, find the last node in the left
  // subtree and insert the new node as its right child.
  //
  // Example 1:
  //   - Current node (this): Node with value 5
  //   - Left subtree:
  //       - Node with value 3
  //           - Left child: Node with value 1
  //           - Right child: Node with value 4
  //   - New node (B): Node with value 2
  //   - Result:
  //       - 4 (last node in left subtree) becomes parent of 2
  //       - 2 becomes right child of 4
  //
  // Example 2:
  //   - Current node (this): Node with value 10
  //   - Left subtree:
  //       - Node with value 5
  //           - Left child: Node with value 2
  //               - Left child: Node with value 1
  //           - Right child: Node with value 7
  //               - Left child: Node with value 6
  //               - Right child: Node with value 8
  //       - Node with value 12
  //           - Left child: Node with value 11
  //           - Right child: Node with value 13
  //   - New node (B): Node with value 9
  //   - Result:
  //       - 8 (last node in left subtree) becomes parent of 9
  //       - 9 becomes right child of 8

  std::shared_ptr<BinaryNode> A = shared_from_this();
  if (left) {
    std::shared_ptr<BinaryNode> A = left->subtree_last();
    A->right = B;
    B->parent = A;
  } else {
    // If the current node has no left child, insert the new node as the left
    // child.
    //
    // Example:
    //   - Current node (this): Node with value 5
    //   - New node (B): Node with value 2
    //   - Result:
    //       - 5 becomes parent of 2
    //       - 2 becomes left child of 5.
    left = B;
    B->parent = shared_from_this();
  }
}

void BinaryNode::subtree_insert_after(std::shared_ptr<BinaryNode> B) {
  // If the current node has a right child, find the first node in the right
  // subtree and insert the new node as its left child.
  //
  // Example 1:
  //   - Current node (this): Node with value 5
  //   - Right subtree:
  //       - Node with value 8
  //           - Left child: Node with value 6
  //           - Right child: Node with value 9
  //   - New node (B): Node with value 7
  //   - Step 1: right->subtree_first() is called on node 8.
  //   - Step 2: subtree_first() on node 8 returns node 6.
  //   - Step 3: 6 becomes the parent of 7, and 7 becomes the left child of 6.
  //   - Result:
  //       - 6 (first node in right subtree) becomes parent of 7
  //       - 7 becomes left child of 6
  //
  // Example 2:
  //   - Current node (this): Node with value 10
  //   - Right subtree:
  //       - Node with value 12
  //           - Left child: Node with value 11
  //           - Right child: Node with value 13
  //               - Left child: Node with value 14
  //                   - Right child: Node with value 15
  //   - New node (B): Node with value 16
  //   - Step 1: right->subtree_first() is called on node 12.
  //   - Step 2: subtree_first() on node 12 returns node 11.
  //   - Step 3: 11 becomes the parent of 16, and 16 becomes the left child
  //   of 11.
  //   - Result:
  //       - 11 (first node in right subtree) becomes parent of 16
  //       - 16 becomes left child of 11

  std::shared_ptr<BinaryNode> A = shared_from_this();
  if (A->right) {
    // std::shared_ptr<BinaryNode> A = right->subtree_first();
    std::shared_ptr<BinaryNode> firstRight = A->right->subtree_first();

    firstRight->left = B;
    B->parent = firstRight;

  } else {
    // If the current node has no right child, insert the new node as the right
    // child.
    //
    // Example:
    //   - Current node (this): Node with value 5
    //   - New node (B): Node with value 7
    //   - Step 1: 5 becomes the parent of 7.
    //   - Step 2: 7 becomes the right child of 5.
    //   - Result:
    //       - 5 becomes parent of 7
    //       - 7 becomes right child of 5.
    //
    // Edge Cases:
    //   - If B is nullptr, no insertion is performed.
    A->right = B;
    B->parent = A;
  }
}

// std::shared_ptr<BinaryNode> BinaryNode::subtree_delete() {
//   // If the node is not a leaf, swap its value with its successor or
//   predecessor
//   // and recursively delete the node with the swapped value.

//   std::shared_ptr<BinaryNode> copy; // Store a copy before potential deletion

//   if (parent.lock() == nullptr) {
//     // If the current node is the root, handle it separately
//     if (!left && !right) {
//       // If the root is a leaf, simply return nullptr to indicate an empty
//       tree return nullptr;
//     } else {
//       // If the root has children, swap with successor/predecessor and
//       continue std::shared_ptr<BinaryNode> B; if (left) {
//         B = predecessor();
//       } else {
//         B = successor();
//       }
//       item = B->item;
//       copy = std::make_shared<BinaryNode>(*B); // Create a copy before
//       deletion B->subtree_delete(); return copy; // Return the copy
//     }
//   }

//   if (left || right) {
//     std::shared_ptr<BinaryNode> B;
//     if (left) {
//       B = predecessor();
//     } else {
//       B = successor();
//     }
//     item = B->item;
//     copy = std::make_shared<BinaryNode>(*B); // Create a copy before deletion
//     B->subtree_delete();
//     return copy; // Return the copy
//   }

//   // If the node is a leaf, detach it from its parent.
//   if (parent.lock()) {
//     delete_leaf()#
//   }

//   copy = std::make_shared<BinaryNode>(*this); // Create a copy before
//   deletion return copy; // Return the copy
// }AA

std::shared_ptr<BinaryNode> BinaryNode::subtree_delete() {
  // Replace the entire method with the following:
  std::shared_ptr<BinaryNode> result = std::make_shared<BinaryNode>(item);

  if (!left && !right) {
    if (auto p = parent.lock()) {
      if (p->left.get() == this) {
        p->left = nullptr;
      } else {
        p->right = nullptr;
      }
    }
    return result;
  }

  std::shared_ptr<BinaryNode> replacement =
      (left) ? predecessor() : successor();
  std::swap(item, replacement->item);
  return replacement->subtree_delete();
}

void BinaryNode::delete_leaf() {
  if (left || right) {
    return;
  }
  if (auto p = parent.lock()) {
    if (p->left.get() == this) {
      p->left = nullptr;
    } else {
      p->right = nullptr;
    }
  }
}

inline BinaryNode::BinaryNode(int item)
    : item(item), parent(), left(nullptr), right(nullptr) {}
