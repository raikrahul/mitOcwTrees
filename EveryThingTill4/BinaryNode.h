// BinaryNode.h

#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <assert.h>
#include <iostream>
#include <memory> // For smart pointers
#include <vector>


class BinaryNode : public std::enable_shared_from_this<BinaryNode> {
public:
  int item;
  std::weak_ptr<BinaryNode> parent;
  std::shared_ptr<BinaryNode> left;
  std::shared_ptr<BinaryNode> right;

  BinaryNode(int item);
  int height();
  void print(std::ostream &out = std::cout);

  std::vector<std::shared_ptr<BinaryNode>> subtree_iter();
  std::shared_ptr<BinaryNode> subtree_first();
  std::shared_ptr<BinaryNode> subtree_last();

  std::shared_ptr<BinaryNode> successor();

  std::shared_ptr<BinaryNode> predecessor();

  void subtree_insert_before(std::shared_ptr<BinaryNode> B);
  void subtree_insert_after(std::shared_ptr<BinaryNode> B);
  // Delete the item contained in the current node from its subtree.
  //
  // Example 1:
  //   - Current node (this): Node with value 5 (leaf node)
  //   - Parent: Node with value 10
  //   - Step 1: Since 5 is a leaf, detach it from its parent (10).
  //   - Result: Node 5 is removed from the tree.
  //
  // Example 2:
  //   - Current node (this): Node with value 10
  //   - Left child: Node with value 5
  //   - Right child: Node with value 15
  //   - Step 1: Since 10 is not a leaf, swap its value with its successor (15).
  //   - Step 2: Recursively call subtree_delete() on the node with the new
  //   value (15).
  //   - Result: Node 15 is removed from the tree.
  //
  // Edge Cases:
  //   - If the current node is nullptr, no deletion is performed.
  std::shared_ptr<BinaryNode> subtree_delete();

private:
  void delete_leaf();
  void subtree_iter_helper(std::vector<std::shared_ptr<BinaryNode>> &nodes);
};

#endif // BINARYNODE_H
