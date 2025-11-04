#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value) {
    std::unique_ptr<BinarySearchTree::Node>* link = &root_;
    while (((*link) != nullptr)) {
        if ((value <= (*link)->value)) {
            link = &((*link)->left);
        } else {
            link = &((*link)->right);
        }
    }
    (*link) = std::make_unique<BinarySearchTree::Node>(value);
}

bool BinarySearchTree::contains(std::int32_t value) const {
    const BinarySearchTree::Node* node = root_.get();
    while ((node != nullptr)) {
        if ((value == node->value)) {
            return true;
        } else {
            if ((value <= node->value)) {
                node = node->left.get();
            } else {
                node = node->right.get();
            }
        }
    }
    return false;
}

bool BinarySearchTree::search(std::int32_t value) const {
    return (contains(value));
}

void BinarySearchTree::in_order_traverse(const BinarySearchTree::Node* node, std::vector<std::int32_t>& out) const {
    if ((node == nullptr)) {
        return;
    } else {
        in_order_traverse(node->left.get(), out);
        out.push_back(node->value);
        in_order_traverse(node->right.get(), out);
    }
}

std::vector<std::int32_t> BinarySearchTree::in_order() const {
    std::vector<std::int32_t> result{};
    in_order_traverse(root_.get(), result);
    return result;
}

}  // namespace binary_search_tree
