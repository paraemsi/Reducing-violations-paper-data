#include "binary_search_tree.h"

namespace binary_search_tree {

// Explicit template instantiations
template class binary_tree<std::int32_t>;
template class binary_tree<std::uint32_t>;
template class binary_tree<std::string>;

template std::unique_ptr<binary_tree<std::int32_t>> make_tree(const std::vector<std::int32_t>&);
template std::unique_ptr<binary_tree<std::uint32_t>> make_tree(const std::vector<std::uint32_t>&);
template std::unique_ptr<binary_tree<std::string>> make_tree(const std::vector<std::string>&);

}  // namespace binary_search_tree
