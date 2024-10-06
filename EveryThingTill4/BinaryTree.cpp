// BinaryTree.cpp

#include "BinaryTree.h"
#include <memory>

void BinaryTree::build(const std::vector<int>& items) {
    root = build_recursive(items, 0, items.size() - 1);
    size = items.size();
}

std::shared_ptr<BinaryNode> BinaryTree::build_recursive(const std::vector<int>& items, int i, int j) {
    if (i > j) {
        return nullptr;
    }
    int c = (i + j) / 2;
    std::shared_ptr<BinaryNode> node = std::make_shared<BinaryNode>(items[c]);
    if (i < c) {
        node->left = build_recursive(items, i, c - 1);
        if (node->left) {
            node->left->parent = node;
        }
    }
    if (c < j) {
        node->right = build_recursive(items, c + 1, j);
        if (node->right) {
            node->right->parent = node;
        }
    }
    return node;
}

//void BinaryTree::insert_at(int i, int x) {
//    std::shared_ptr<BinaryNode> new_node = std::make_shared<BinaryNode>(x);
//    if (i == 0) {
//        // Insert at the beginning
//        if (root) {
//            std::shared_ptr<BinaryNode> first = root;
//            while (first->left) {
//                first = first->left;
//            }
//            first->subtree_insert_before(new_node);
//        }
//        else {
//            root = new_node;
//        }
//    }
//    else {
//        // Insert after a specific node
//        std::shared_ptr<BinaryNode> node = find_node_by_index(i - 1);
//        if (node) {
//            node->subtree_insert_after(new_node);
//        }
//        // Handle the case where i is out of bounds (optional)
//    }
//    size++;
//}
//
//void BinaryTree::delete_at(int i) {
//    std::shared_ptr<BinaryNode> node = find_node_by_index(i);
//    if (node) {
//        node->subtree_delete();
//        size--;
//    }
//    // Handle the case where i is out of bounds (optional)
//}
//
//void BinaryTree::print(std::ostream& out) {
//    if (root) {
//        root->print(out);
//    }
//    out << std::endl;
//}
//
//std::shared_ptr<BinaryNode> BinaryTree::find_node_by_index(int index) {
//    if (!root || index < 0 || index >= size) {
//        return nullptr; // Handle invalid input
//    }
//
//    std::shared_ptr<BinaryNode> current = root;
//    int currentIndex = (current->left) ? current->left->size : 0;
//
//    while (current) {
//        if (currentIndex == index) {
//            return current;
//        }
//        else if (index < currentIndex) {
//            current = current->left;
//        }
//        else {
//            index -= (currentIndex + 1);
//            current = current->right;
//        }
//
//        if (current) {
//            currentIndex = (current->left) ? current->left->size : 0;
//        }
//    }
//
//    return nullptr; // Node not found
//}