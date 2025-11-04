#include "binary_search_tree.h"
#if 0

namespace binary_search_tree {

binary_tree::binary_tree(int value)
    : m_data{value}, m_left{nullptr}, m_right{nullptr} {}

int binary_tree::data() const {
    return m_data;
}

const binary_tree* binary_tree::left() const {
    return m_left.get();
}

const binary_tree* binary_tree::right() const {
    return m_right.get();
}

void binary_tree::insert(int value) {
    if (value <= m_data) {
        if (m_left) {
            m_left->insert(value);
        } else {
            m_left = std::unique_ptr<binary_tree>(new binary_tree(value));
        }
    } else {
        if (m_right) {
            m_right->insert(value);
        } else {
            m_right = std::unique_ptr<binary_tree>(new binary_tree(value));
        }
    }
}

std::vector<int> binary_tree::sorted_data() const {
    std::vector<int> result;
    if (m_left) {
        auto left_vec = m_left->sorted_data();
        result.insert(result.end(), left_vec.begin(), left_vec.end());
    }

    result.push_back(m_data);

    if (m_right) {
        auto right_vec = m_right->sorted_data();
        result.insert(result.end(), right_vec.begin(), right_vec.end());
    }
    return result;
}

}  // namespace binary_search_tree
#endif
