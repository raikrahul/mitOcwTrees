// BinaryTree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"
#include <vector>
#include <memory>

class BinaryTree {
public:
    std::shared_ptr<BinaryNode> root;
    int size;

    BinaryTree() : root(nullptr), size(0) {}

    int get_size() {
        return size;
    }

    // Construct a binary tree from a vector of items.
    //
    // Example:
    //   - Input vector: [1, 2, 3, 4, 5]
    //   - Result: A balanced binary tree with the following structure:
    //
    //       3
    //      / \
    //     2   5
    //    /   /
    //   1   4
    void build(const std::vector<int>& items);

    // Insert a new node with value x at index i in the traversal order.
    //
    // Example:
    //   - Current tree: (see above)
    //   - x: 6
    //   - i: 3
    //   - Result: The tree is modified to:
    //
    //       3
    //      / \
    //     2   5
    //    /   / \
    //   1   4   6
    void insert_at(int i, int x);

    // Delete the node at index i in the traversal order.
    //
    // Example:
    //   - Current tree: (see above)
    //   - i: 2
    //   - Result: The tree is modified to:
    //
    //       3
    //      / \
    //     2   6
    //    /   /
    //   1   4
    void delete_at(int i);

    // Print the tree in inorder traversal order.
    void print(std::ostream& out = std::cout);

private:
    // Recursive helper function for build()
    std::shared_ptr<BinaryNode> build_recursive(const std::vector<int>& items, int i, int j);

    // Helper function to find a node by its index in the traversal order
    std::shared_ptr<BinaryNode> find_node_by_index(int index);
};

#endif // BINARYTREE_H