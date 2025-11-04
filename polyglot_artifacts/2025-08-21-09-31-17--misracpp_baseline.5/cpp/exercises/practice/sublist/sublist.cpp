#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

template <typename T>
static bool is_sublist(const std::vector<T>& small, const std::vector<T>& big) {
    if (small.empty()) return true;
    if (small.size() > big.size()) return false;
    for (size_t i = 0; i <= big.size() - small.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < small.size(); ++j) {
            if (big[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

template <typename T>
Comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return Comparison::equal;
    }
    if (is_sublist(a, b)) {
        return Comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return Comparison::superlist;
    }
    return Comparison::unequal;
}

// Explicit template instantiations for common types
template Comparison sublist<int>(const std::vector<int>&, const std::vector<int>&);
template Comparison sublist<long>(const std::vector<long>&, const std::vector<long>&);
template Comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);
template Comparison sublist<std::string>(const std::vector<std::string>&, const std::vector<std::string>&);

}  // namespace sublist
