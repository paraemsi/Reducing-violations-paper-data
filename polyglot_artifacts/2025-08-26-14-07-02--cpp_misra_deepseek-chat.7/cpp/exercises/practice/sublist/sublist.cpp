#include "sublist.h"
#include <vector>
#include <string>

namespace sublist {

// Explicit instantiations for common types
template List_comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
template List_comparison sublist<double>(const std::vector<double>&, const std::vector<double>&);
template List_comparison sublist<std::string>(const std::vector<std::string>&, const std::vector<std::string>&);
template List_comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);
// Add more if needed

}  // namespace sublist
