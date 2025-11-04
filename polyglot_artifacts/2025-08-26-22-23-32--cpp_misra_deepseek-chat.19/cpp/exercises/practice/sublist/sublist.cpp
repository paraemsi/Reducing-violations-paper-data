#include "sublist.h"
#include <vector>

namespace sublist {

// Explicit template instantiations
template bool is_sublist<int>(const std::vector<int>&, const std::vector<int>&);
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
