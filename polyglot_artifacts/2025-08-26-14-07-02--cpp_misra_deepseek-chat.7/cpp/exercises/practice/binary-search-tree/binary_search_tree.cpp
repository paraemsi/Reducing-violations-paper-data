#include "binary_search_tree.h"
#include <memory>
#include <cstdint>
#include <vector>

namespace binary_search_tree {

// Explicit instantiations
template class binary_tree<std::int32_t>;
template class binary_tree<std::string>;

template std::unique_ptr<binary_tree<std::int32_t>> make_tree(const std::vector<std::int32_t>& values);
template std::unique_ptr<binary_tree<std::string>> make_tree(const std::vector<std::string>& values);

}  // namespace binary_search_tree
