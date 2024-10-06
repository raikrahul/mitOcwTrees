// BSTNode.h

#ifndef BSTNODE_H
#define BSTNODE_H

#include "BinaryNode.h"
#include <memory>

class BSTNode : public BinaryNode {
public:
    BSTNode(int item) : BinaryNode(item) {}

     std::shared_ptr<BSTNode> subtree_find(int k);
    void subtree_test_find();
    std::shared_ptr<BSTNode> subtree_find_next(int k);
    std::shared_ptr<BSTNode> subtree_find_prev(int k);
    void subtree_insert(std::shared_ptr<BSTNode> B);

};

#endif // BSTNODE_H