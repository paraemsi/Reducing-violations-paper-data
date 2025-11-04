#include "binary_search_tree.h"
#include <cstdint>

namespace binary_search_tree {

// Explicit instantiation for int32_t
template class binary_tree<std::int32_t>;
template binary_tree<std::int32_t> make_tree(const std::vector<std::int32_t>& values);

// Explicit instantiation for std::string
template class binary_tree<std::string>;
template binary_tree<std::string> make_tree(const std::vector<std::string>& values);

}  // namespace binary_search_tree
