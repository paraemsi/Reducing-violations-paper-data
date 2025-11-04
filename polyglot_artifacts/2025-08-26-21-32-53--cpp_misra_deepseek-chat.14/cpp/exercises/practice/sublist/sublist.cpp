#include "sublist.h"
#include <vector>

namespace sublist {

// Explicit template instantiations
template bool is_sublist<int>(const std::vector<int>&, const std::vector<int>&);
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);

// Add instantiations for other types if needed
template bool is_sublist<double>(const std::vector<double>&, const std::vector<double>&);
template List_comparison sublist<double>(const std::vector<double>&, const std::vector<double>&);

template bool is_sublist<char>(const std::vector<char>&, const std::vector<char>&);
template List_comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);

}  // namespace sublist
