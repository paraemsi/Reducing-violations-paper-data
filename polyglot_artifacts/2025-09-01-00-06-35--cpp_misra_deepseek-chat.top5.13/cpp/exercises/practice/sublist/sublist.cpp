#include "sublist.h"

namespace sublist {

// Explicit instantiation for int to satisfy the tests
template bool is_sublist<int>(const std::vector<int>&, const std::vector<int>&);
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
