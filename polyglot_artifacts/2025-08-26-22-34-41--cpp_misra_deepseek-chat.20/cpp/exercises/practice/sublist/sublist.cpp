#include "sublist.h"

namespace sublist {

// Explicit template instantiations
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
template List_comparison sublist<double>(const std::vector<double>&, const std::vector<double>&);
template List_comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);
// Add more types if needed

}  // namespace sublist
