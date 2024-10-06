// BSTNodeTest.cpp

#include "Set.h"
#include "SetTest.h"
#include <cassert>
#include <iostream>
#include <memory>

void SetTest::testFind() {
  // Construct a sample BST
  auto root = std::make_shared<BSTNode>(8);
  root->left = std::make_shared<BSTNode>(3);
  root->left->parent = root;
  root->right = std::make_shared<BSTNode>(10);
  root->right->parent = root;
  root->left->left = std::make_shared<BSTNode>(1);
  root->left->left->parent = root->left;
  root->left->right = std::make_shared<BSTNode>(6);
  root->left->right->parent = root->left;
  root->right->right = std::make_shared<BSTNode>(14);
  root->right->right->parent = root->right;
  root->right->right->left = std::make_shared<BSTNode>(13);
  root->right->right->left->parent = root->right->right;

  // Test cases
  std::shared_ptr<BSTNode> node = root->subtree_find(8);
  assert(node != nullptr);
  assert(node->item == 8);

  node = root->subtree_find(13);
  assert(node != nullptr);
  assert(node->item == 13);

  node = root->subtree_find(1);
  assert(node != nullptr);
  assert(node->item == 1);

  node = root->subtree_find(100);
  assert(node == nullptr);

  std::cout << "subtree_test_find passed!" << std::endl;
}