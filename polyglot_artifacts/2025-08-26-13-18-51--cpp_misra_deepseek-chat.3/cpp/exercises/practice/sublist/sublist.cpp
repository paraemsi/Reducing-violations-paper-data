#include "sublist.h"

namespace sublist {

// Explicit template instantiation for int
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
