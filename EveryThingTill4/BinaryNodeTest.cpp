// BinaryNodeTest.cpp

#include "BinaryNode.h"
#include <cassert>
#include <sstream>

namespace BinaryNodeTest {

// Test the height() function
// Expected: Correctly calculates the height of various tree structures
// Why: Height is a fundamental property of trees and is used in many algorithms
void testHeight() {
    auto root = std::make_shared<BinaryNode>(1);
    assert(root->height() == 0);

    root->left = std::make_shared<BinaryNode>(2);
    root->left->parent = root;
    assert(root->height() == 1);

    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;
    assert(root->height() == 1);

    root->left->left = std::make_shared<BinaryNode>(4);
    root->left->left->parent = root->left;
    assert(root->height() == 2);
}

// Test the print() function
// Expected: Correctly prints the tree in-order
// Why: In-order traversal is a common way to represent sorted data in a BST
void testPrint() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    std::ostringstream oss;
    root->print(oss);
    assert(oss.str() == "1 2 3 ");
}

// Test the subtree_iter() function
// Expected: Returns nodes in the correct in-order traversal
// Why: Iterating over a tree is a fundamental operation for many algorithms
void testSubtreeIter() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    auto nodes = root->subtree_iter();
    assert(nodes.size() == 3);
    assert(nodes[0]->item == 1);
    assert(nodes[1]->item == 2);
    assert(nodes[2]->item == 3);
}

// Test the subtree_first() function
// Expected: Returns the leftmost node in the subtree
// Why: Finding the first (smallest) element is crucial for many BST operations
void testSubtreeFirst() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    assert(root->subtree_first()->item == 1);
    assert(root->right->subtree_first()->item == 3);
}

// Test the subtree_last() function
// Expected: Returns the rightmost node in the subtree
// Why: Finding the last (largest) element is crucial for many BST operations
void testSubtreeLast() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    assert(root->subtree_last()->item == 3);
    assert(root->left->subtree_last()->item == 1);
}

// Test the successor() function
// Expected: Returns the next node in in-order traversal
// Why: Finding the successor is essential for iterating and maintaining BST properties
void testSuccessor() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    assert(root->left->successor()->item == 2);
    assert(root->successor()->item == 3);
    assert(root->right->successor() == nullptr);
}

// Test the predecessor() function
// Expected: Returns the previous node in in-order traversal
// Why: Finding the predecessor is essential for reverse iteration and maintaining BST properties
void testPredecessor() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    assert(root->right->predecessor()->item == 2);
    assert(root->predecessor()->item == 1);
    assert(root->left->predecessor() == nullptr);
}

// Test the subtree_insert_before() function
// Expected: Correctly inserts a new node before the current node
// Why: Insertion is a fundamental operation for building and modifying BSTs
void testSubtreeInsertBefore() {
    auto root = std::make_shared<BinaryNode>(2);
    auto newNode = std::make_shared<BinaryNode>(1);
    root->subtree_insert_before(newNode);

    assert(root->left == newNode);
    assert(newNode->parent.lock() == root);
}

// Test the subtree_insert_after() function
// Expected: Correctly inserts a new node after the current node
// Why: Insertion is a fundamental operation for building and modifying BSTs
void testSubtreeInsertAfter() {
    auto root = std::make_shared<BinaryNode>(2);
    auto newNode = std::make_shared<BinaryNode>(3);
    root->subtree_insert_after(newNode);

    assert(root->right == newNode);
    assert(newNode->parent.lock() == root);
}

// Test the subtree_delete() function
// Expected: Correctly deletes a node and restructures the tree
// Why: Deletion is a crucial operation for maintaining BSTs and freeing memory
void testSubtreeDelete() {
    auto root = std::make_shared<BinaryNode>(2);
    root->left = std::make_shared<BinaryNode>(1);
    root->left->parent = root;
    root->right = std::make_shared<BinaryNode>(3);
    root->right->parent = root;

    auto deleted = root->left->subtree_delete();
    assert(deleted->item == 1);
    assert(root->left == nullptr);

    deleted = root->subtree_delete();
    assert(deleted->item == 2);
    assert(root->parent.expired());
}

} // namespace BinaryNodeTest
